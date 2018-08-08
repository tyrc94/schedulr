import sqlite3
from flask import g, Flask
app = Flask(__name__)

DATABASE = './src/db/database.db'

def make_dicts(cursor, row):
    return dict((cursor.description[idx][0], value)
                for idx, value in enumerate(row))


def init_db():
    with app.app_context():
        db = get_db()
        with app.open_resource('schema.sql', mode='r') as f:
            db.cursor().executescript(f.read())
        db.commit()


def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = sqlite3.connect(DATABASE)

    db.row_factory = make_dicts
    return db


def mutate_db(query, args=()):
    db = get_db()
    db.execute(query, args)
    db.commit()
    return True


def query_db(query, args=(), one=False):
    cur = get_db().execute(query, args)
    rv = cur.fetchall()
    cur.close()
    return (rv[0] if rv else None) if one else rv


@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()


def check_login(username, password):
    user = query_db('SELECT * FROM User WHERE email = ? AND password = ?',
                [username, password], one=True)
    if user is None:
        return False
    else:
        return user


def register(username, password, forename, surname):
    try:
        _ = mutate_db("INSERT INTO users (username, password, forename, surname) VALUES (?,?,?,?)",
                    [username, password, forename, surname])
        return True
    except Exception as e:
        return False


def user_details(user_id):
    return query_db('SELECT * FROM users WHERE id = ?', [user_id])


def create_task(name, description, priority):
    return mutate_db("INSERT INTO tasks (name, description, priority_id) VALUES (?, ?, ?)", 
                [name, description, priority])


def update_task(task_id, name = None, description = None, priority = None):
    task = {'name': name, 'description': description, 'priority': priority}
    task_update = {k: v for k, v in task if v is not None}
    for arg in task_update:
        mutate_db("UPDATE tasks SET ? = ? WHERE task_id = ?", [task, task_update[arg], task_id])


def delete_task(task_id):
    return mutate_db("DELETE FROM tasks WHERE id = ?", task_id)


def add_collaborators(task_id, user_ids):
    for user_id in user_ids:
        mutate_db("INSERT INTO collaborators (user_id, task_id) VALUES (?, ?)", [task_id, user_id])


def remove_collaborators(task_id, user_ids):
    for user_id in user_ids:
        mutate_db("DELETE FROM collaborators WHERE task_id = ? AND user_id = ?", [task_id, user_id])