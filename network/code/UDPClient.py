from socket import *

serverName = 'xxx.xxx.xxx.xxx'
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_DGRAM)
message = input("Input lowercase sentence: ")
clientSocket.sendto(message.encode(), (serverName, serverPort))
print("have sent message \"", message, "\" to", serverName)
modifiedMessage, serverAddress = clientSocket.recvfrom(2048)
print(modifiedMessage.decode())
clientSocket.close()
