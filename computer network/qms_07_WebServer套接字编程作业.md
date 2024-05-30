# WebServer套接字编程作业

## 目标

实现一个 Web 服务器，可以在浏览器上访问

## 代码

>   code 文件夹下 WebServer.py

```python
from socket import *

serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', 80))  # http 默认使用 80 端口
serverSocket.listen(1)  # 最大连接数为1
while True:
    # Establish the connection
    print('Ready to serve...')
    connectionSocket, addr = serverSocket.accept()
    try:
        message = connectionSocket.recv(2048)
        filename = message.split()[1]
        f = open(filename[1:])
        outputdata = f.read()

        # Send one HTTP header line into socket
        header = ' HTTP/1.1 200 OK\nConnection: close\nContent-Type: text/html\nContent-Length: %d\n\n' % (
            len(outputdata))
        connectionSocket.send(header.encode())

        # Send the content of the requested file to the client
        for i in range(0, len(outputdata)):
            connectionSocket.send(outputdata[i].encode())
        connectionSocket.send("\r\n".encode())

        connectionSocket.close()
    except IOError:
        # Send response message for file not found
        header = ' HTTP/1.1 404 Found'
        connectionSocket.send(header.encode())
        # Close client socket
        connectionSocket.close()

```

为了传输具体的 html 网页，再编写一个简单 html 文件

>   code 文件夹下 HelloWorld.html

```html
<h1>Hello World!</h1>
```

## 部署

将两个文件都放在远程服务器上，运行 WebServer.py

## 结果

![找到文件](https://i.niupic.com/images/2022/11/06/aakF.JPG)

![找不到文件](https://i.niupic.com/images/2022/11/06/aakE.JPG)