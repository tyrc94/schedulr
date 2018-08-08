from flask import Flask, request, redirect, render_template, send_from_directory, jsonify
import json
import jwt

import db.db

app = Flask(__name__)
db.db.init_db()

@app.route('/', methods = ['GET'])
def server_html():
    return send_from_directory('client/src/', 'index.html')


@app.route('/Index.js', methods = ['GET'])
def server_js():
    return send_from_directory('client/build/', 'Index.js')


@app.route('/signup', methods = ['POST'])
def signup():
    data = request.get_json()

    success = db.db.register(
                                data.get('username'),
                                data.get('password'),
                                data.get('forename'),
                                data.get('surname')  
                            )  

    if not success:
        return "ERROR", 400
    else:
        identity = {
                'username': data.get('username'),
                'password': data.get('password'),
                'forename': data.get('forename'),
                'surname': data.get('surname') 
            }

        return jsonify(identity)
        

@app.route('/authenticate/login', methods = ['POST'])
def authenticate():
    data = request.get_json()

    user = db.db.check_login(data.get('username'), data.get('password'))
    if not user:
        failure = {'message': 'Invalid credentials', 'status': 401}
        return jsonify(failure), 401
    else:
        token = jwt.encode({'user_id': user['id']}, 'secret', algorithm='HS256').decode('utf-8')
        success = {
            'user_id': user['id'],
            'username': user['username'],
            'forename': user['forename'],
            'surname': user['surname'],
            'token': str(token)
        }
        return jsonify(success)


@app.route('/user/<user_id>', methods = ['GET'])
def get_user(user_id):
    user_info = db.db.user_details(user_id)
    return jsonify(user_info)


@app.route('/task/create', methods = ['POST'])
def create_task():
    token = request.headers.get('Authorization')

    try:
        user = jwt.decode(token, 'secret', algorithms=['HS256'])
    except Exception as e:
        print(e)
        return "Unauthorized", 403


    data = request.get_json()

    task_details = {
        'name': data.get('name'),
        'description': data.get('description'),
        'priority': data.get('priority'),
        'owner_id': user['user_id']
    }

    db.db.create_task(**task_details)
    return jsonify(task_details)


@app.route('/task/add_collaborators', methods = ['POST'])
def add_collaborators():
    data = request.get_json()

    collaborators = data.get('username')
    collaborator_ids = [db.db.find_user_id(x)[0]['id'] for x in collaborators]

    add = {
        'task_id': int(data.get('task_id')),
        'user_ids': collaborator_ids
    }
    
    db.db.add_collaborators(**add)

    return jsonify(add)

@app.route('/task/remove_collaborators', methods = ['POST'])
def remove_collaborators():
    data = request.get_json()

    collaborators = data.get('username')
    collaborator_ids = [db.db.find_user_id(x)[0]['id'] for x in collaborators]

    remove = {
        'task_id': int(data.get('task_id')),
        'user_ids': collaborator_ids
    }
    
    try:
        db.db.remove_collaborators(**remove)
        return jsonify(remove)
    except Exception as e:
        return e


if __name__ == "__main__":
    app.run()