
from flask import Flask, request, jsonify
from flask_cors import CORS, cross_origin
import json
import jsonpickle




app = Flask(__name__)
cors = CORS(app)
app.config['CORS_HEADERS'] = 'Content-Type'

# ROUTE TEST


@app.route('/test')
@cross_origin()
def test():
    return "Successful"


if __name__ == "__main__":
    app.run(debug=True, host='0.0.0.0', port=8080)
