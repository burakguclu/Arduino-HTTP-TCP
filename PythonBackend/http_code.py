from flask import Flask, jsonify, request

app = Flask(__name__)

users = [
    {"id": 1, "name": "Ali"},
    {"id": 2, "name": "Ahmet"}
]

@app.route("/users", methods=["GET"])
def get_users():
    return jsonify(users)

@app.route("/users/<int:user_id>", methods=["GET"])
def get_user(user_id):
    user = next((u for u in users if u["id"] == user_id), None)
    return jsonify(user) if user else ("User not found", 404)

@app.route("/users", methods=["POST"])
def add_user():
    data = request.json
    new_user = {"id": len(users) + 1, "name": data["name"]}
    users.append(new_user)
    return jsonify(new_user), 201

if __name__ == "__main__":
    app.run(debug=True)
