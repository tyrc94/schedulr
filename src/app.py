from flask import Flask, request, redirect, render_template, send_from_directory, jsonify
import json

import db.db

app = Flask(__name__)
db.db.init_db()

@app.route('/', methods = ['GET'])
def server_html():
    return send_from_directory('client/src/', 'index.html')


@app.route('/Index.js', methods = ['GET'])
def server_js():
    return send_from_directory('client/build/', 'Index.js')


@app.route('/user/<user_id>', methods = ['GET'])
def get_user(user_id):
    user_info = db.db.user_details(user_id)
    return jsonify(user_info)


if __name__ == "__main__":
    app.run()