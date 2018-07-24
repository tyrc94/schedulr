from flask import Flask, request, redirect, render_template, send_from_directory

app = Flask(__name__)

@app.route('/', methods = ['GET'])
def something():
    return send_from_directory('client/src/', 'index.html')

@app.route('/Index.js', methods = ['GET'])
def something_else():
    return send_from_directory('client/build/', 'Index.js')