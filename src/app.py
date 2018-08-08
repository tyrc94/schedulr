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
        return "ERROR"
    else:
        identity = {
                'username': data.get('username'),
                'password': data.get('password'),
                'forename': data.get('forename'),
                'surname': data.get('surname') 
            }

        return jsonify(identity), 200

        

@app.route('/authenticate/login', methods = ['POST'])
def authenticate():
    data = request.get_json()

    user = db.db.check_login(data.get('username'), data.get('password'))
    if not user:
        failure = {'message': 'Invalid credentials', 'status': 401}
        return jsonify(failure)
    else:
        token = jwt.encode({'user_id': user['id']}, 'secret', algorithm='HS256')
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
    data = request.get_json()

    task_details = {
        'name': data.get('name'),
        'description': data.get('description'),
        'priority': data.get('priority')
    }

    db.db.create_task(**task_details)
    return jsonify(task_details)

if __name__ == "__main__":
    app.run()