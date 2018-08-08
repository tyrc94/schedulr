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
    success = db.db.register(
                                request.get_json('username'),
                                request.get_json('password'),
                                request.get_json('forename'),
                                request.get_json('surname')  
                            )  

    if success:
        identity = {
                'username': request.get_json('username'),
                'password': request.get_json('password'),
                'forename': request.get_json('forename'),
                'surname': request.get_json('surname') 
            }
        return jsonify(identity)
        

@app.route('/authenticate/login', methods = ['POST'])
def authenticate():
    user = db.db.check_login(request.get_json['user'], request.get_json['password'])
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
            'token': token
        }
        return jsonify(success)


@app.route('/user/<user_id>', methods = ['GET'])
def get_user(user_id):
    user_info = db.db.user_details(user_id)
    return jsonify(user_info)


@app.route('/task/create', methods = ['POST'])
def create_task():

    task_details = {
        'name': request.get_json('name'),
        'description': request.get_json('description'),
        'priority': request.get_json('priority')
    }

    db.db.create_task(**task_details)
    return jsonify(task_details)

if __name__ == "__main__":
    app.run()