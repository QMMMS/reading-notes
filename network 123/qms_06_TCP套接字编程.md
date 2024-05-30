# TCP套接字编程

## 目标

1.   在本地客户端输入一段字符串
2.   发送给服务器
3.   服务器把字符串改为全大写
4.   发送给本地客户端
5.   本地客户端显示修改过的字符串

## 客户端代码

>   code 文件夹下 TCPClient.py

```python
from socket import *

serverName = 'xxx.xxx.xxx.xxx' # 把远程服务器的ip或主机名填这里
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM) # 指示网络选择IPv4和TCP
clientSocket.connect((serverName, serverPort)) # TCP 需要先建立连接
message = input("Input lowercase sentence: ")
clientSocket.send(message.encode())
print("have sent message \"", message, "\" to", serverName)
modifiedMessage = clientSocket.recv(2048)
print(modifiedMessage.decode())
clientSocket.close()
```

## 服务器端代码

>   code 文件夹下 TCPServer.py

```python
from socket import *

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM) # 指示网络选择IPv4和TCP
serverSocket.bind(('', serverPort)) # 绑定本机ip和端口
serverSocket.listen(1) # 等待某个用户来连接
print("The server is ready to receive")
while True:
    connectionSocket, addr = serverSocket.accept() # 接收连接请求，创建连接
    message = connectionSocket.recv(2048).decode() # 从客户端接收信息，2048表示缓存
    print("receive from", addr, ": ", message)
    modifiedMessage = message.upper()
    connectionSocket.send(modifiedMessage.encode()) # 发给客户端
    print("have sent message back: ", modifiedMessage)
```

## 运行实例

**客户端：**

```
Input lowercase sentence: hello tcp
have sent message " hello tcp " to xxx.xxx.xxx.xxx
HELLO TCP
```

**服务器端：**

```
The server is ready to receive
receive from ('xxx.xxx.xxx.xxx', 6460) :  hello tcp
have sent message back:  HELLO TCP
```

