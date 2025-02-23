import socket

HOST = "0.0.0.0"
PORT = 80

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(5)

print(f"Sunucu başlatıldı. {PORT} portunda dinleniyor...")

while True:
    client_socket, client_address = server_socket.accept()
    print(f"Bağlantı sağlandı: {client_address}")

    while True:
        try:
            data = client_socket.recv(1024)
            if not data:
                break

            message = data.decode("utf-8")
            print(f"Arduino'dan gelen mesaj: {message}")

            client_socket.sendall("Mesaj alındı!".encode())

        except ConnectionResetError:
            print("Bağlantı kesildi.")
            break

    client_socket.close()
