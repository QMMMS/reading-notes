from socket import *

serverName = 'xxx.xxx.xxx.xxx'
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
message = input("Input lowercase sentence: ")
clientSocket.send(message.encode())
print("have sent message \"", message, "\" to", serverName)
modifiedMessage = clientSocket.recv(2048)
print(modifiedMessage.decode())
clientSocket.close()
