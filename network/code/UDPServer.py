from socket import *
serverPort = 12000
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('', serverPort))
print("The server is ready to receive")
while True:
    message, clientAddress = serverSocket.recvfrom(2048)
    print("receive from", clientAddress, ": ", message.decode())
    modifiedMessage = message.decode().upper()
    print("have sent message back: ", modifiedMessage)
    serverSocket.sendto(modifiedMessage.encode(), clientAddress)
