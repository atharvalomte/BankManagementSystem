from flask import Flask, request, jsonify
from flask_cors import CORS
import subprocess
import os

app = Flask(__name__)
CORS(app)  

BINARY_NAME = './bank_system.exe' if os.name == 'nt' else './bank_system'

@app.route('/api/bank', methods=['POST'])
def process_transaction():
    data = request.json
    choice = str(data.get('choice'))
    args = [str(arg) for arg in data.get('args', [])]
    
   
    input_sequence = [choice] + args + ["7"] 
    input_string = "\n".join(input_sequence) + "\n"
    
    try:
        process = subprocess.Popen(
            [BINARY_NAME], 
            stdin=subprocess.PIPE, 
            stdout=subprocess.PIPE, 
            stderr=subprocess.PIPE, 
            text=True
        )
        
        stdout, stderr = process.communicate(input=input_string)
        
        return jsonify({
            "status": "success",
            "output": stdout.strip(),
            "errors": stderr.strip()
        })
        
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

if __name__ == '__main__':
    app.run(port=18080, debug=True)