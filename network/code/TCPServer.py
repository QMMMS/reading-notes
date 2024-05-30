from socket import *

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))
serverSocket.listen(1)
print("The server is ready to receive")
while True:
    connectionSocket, addr = serverSocket.accept()
    message = connectionSocket.recv(2048).decode()
    print("receive from", addr, ": ", message)
    modifiedMessage = message.upper()
    connectionSocket.send(modifiedMessage.encode())
    print("have sent message back: ", modifiedMessage)
