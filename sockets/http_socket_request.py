import socket

def http_socket(url, port=80, path='/'):
    try:
        mysock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error as e:
        print(f"Failed to create socket: {e}")
        return 
    try:
        host = socket.gethostbyname(url)
    except socket.gaierror as e:
        print(f"Failed to get host: {e}")
        return
        
    mysock.connect((host, port))
    message = f"GET {path} HTTP/1.1\r\nHost: {url}\r\nConnection: close\r\n\r\n"
    try:
        mysock.sendall(message.encode('utf-8'))
        response = b""
        while True:
            data= mysock.recv(1000)
            if not data:
                break
            response += data
            mysock.close()
            return response.decode('utf-8')
    except socket.error:
        print("Failed to send")

port = 80
url = "www.example.com"

data = http_socket(url, port=port)
if data:
    print(data)