# UDP套接字编程

## 目标

1.   在本地客户端输入一段字符串
2.   发送给服务器
3.   服务器把字符串改为全大写
4.   发送给本地客户端
5.   本地客户端显示修改过的字符串

## 准备

当然要两台电脑，或者虚拟机，或者租一个远程服务器

作者租了一个远程服务器，Linux 系统，提前把 python3 之类的环境配置好

如果远程服务器开了防火墙，记得把相关端口允许放行，或者短暂关闭防火墙

## 客户端代码

>   code 文件夹下 UDPClient.py

```python
from socket import *

serverName = 'xxx.xxx.xxx.xxx' # 把远程服务器的ip或主机名填这里
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_DGRAM) # 指示网络选择IPv4和UDP
message = input("Input lowercase sentence: ")
clientSocket.sendto(message.encode(), (serverName, serverPort)) # 发送信息
print("have sent message \"", message, "\" to", serverName)
modifiedMessage, serverAddress = clientSocket.recvfrom(2048) # 接收信息，2048表示缓存长度
print(modifiedMessage.decode())
clientSocket.close()
```

## 服务器端代码

>   code 文件夹下 UDPServer.py

```python
from socket import *

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_DGRAM) # 指示网络选择IPv4和UDP
serverSocket.bind(('', serverPort)) # 绑定本机ip和端口
print("The server is ready to receive")
while True:
    message, clientAddress = serverSocket.recvfrom(2048) # 从客户端接收信息，2048表示缓存长度
    print("receive from", clientAddress, ": ", message.decode())
    modifiedMessage = message.decode().upper() # 转大写
    print("have sent message back: ", modifiedMessage)
    serverSocket.sendto(modifiedMessage.encode(), clientAddress) # 发给客户端
```

## 运行实例

当然，服务器端的代码要先开始运行，然后打开客户端输入

**客户端：**

```
Input lowercase sentence: hello world
have sent message " hello world " to xxx.xxx.xxx.xxx
HELLO WORLD
```

**服务器端：**

```
The server is ready to receive
receive from ('xxx.xxx.xxx.xxx', xxxx) :  hello world
have sent message back:  HELLO WORLD
```

