# 实验

## telnet 与 HTTP 实验

`telnet`命令可以手动编辑和发送报文，Linux 和 Windows 都可以使用

找了一个远程 Linux 服务器进行实验

系统为 CentOS，想要安装`telnet`命令，root 使用命令：

```shell
yum install telnet
```

这里用书上的例子

```
[root@qmmms ~]# telnet gaia.cs.umass.edu 80
Trying 128.119.245.12...
Connected to gaia.cs.umass.edu.
Escape character is '^]'.
GET /kurose_ross/interactive/index.php HTTP/1.1
Host: gaia.cs.umass.edu

```

注意最后按两下回车结束，得到结果：

```
HTTP/1.1 200 OK
Date: Fri, 30 Sep 2022 07:11:13 GMT
Server: Apache/2.4.6 (CentOS) OpenSSL/1.0.2k-fips PHP/7.4.30 mod_perl/2.0.11 Perl/v5.16.3
X-Powered-By: PHP/7.4.30
Set-Cookie: DevMode=0
Transfer-Encoding: chunked
Content-Type: text/html; charset=UTF-8

361c

<!DOCTYPE HTML>
<html>

  [...省略...]
```

> 补充：使用Chrome浏览器，进入开发者模式，进入网络，随便选一个请求，可以看到报文

## telnet 与 SMTP 实验

SMTP 是电子邮件使用的应用层协议，同样可以使用`telnet`命令手动模拟

发邮件一端可以使用远程 Linux 主机

使用 SMTP 协议的邮件服务器比较难找，试了试，学校(DUT)邮箱可以用

**用户端需要手动键入的信息有：**

```
HELO xxx.xxx.xxx.x					#我的远程主机
MAIL FROM: <用户@xxx.xxx.xxx.x>		#发送方
RCPT TO: <用户@对方地址>				#收件方
DATA								#开始输入正文
.									#以单行.作为正文结束
QUIT								#结束连接
```

**全部实验过程：**

```
[user1@qmmms ~]$ telnet mail.dlut.edu.cn 25
Trying 202.118.66.82...
Connected to mail.dlut.edu.cn.
Escape character is '^]'.
220 mail.dlut.edu.cn ESMTP mail service ready
HELO xxx.xxx.xxx.x
250 OK
MAIL FROM: <user1@xxx.xxx.xxx.x>
250 Mail OK
RCPT TO: <xxxxxxx@mail.dlut.edu.cn>
250 Mail OK
DATA
354 End data with <CR><LF>.<CR><LF>
hello from linux
.
250 Mail OK queued as UEJ2ygBnb+8toTZjKwx_CA--.36240S2
QUIT
221 Bye
Connection closed by foreign host.
```

最后在学校邮箱的垃圾邮件里面找到了这个邮件

> 补充：就现在而言（2022），大部分电子邮件功能支持都以网页版形式呈现，发邮件可以使用 SMTP 协议，查收邮件 HTTP 协议（通过网页）

## telnet 与 POP3 实验

POP3协议，用于接收邮件，同样可以使用`telnet`命令手动模拟

**用户端需要手动键入的信息有：**

```
user 账号
pass 密码
list			#列出所有邮件
retr 数字			#查看数字标识的邮件
dele 数字			#删除数字标识的邮件
quit			#退出
```

**全部实验过程：**

```
[user1@qmmms ~]$ telnet mail.dlut.edu.cn 110
Trying 202.118.66.82...
Connected to mail.dlut.edu.cn.
Escape character is '^]'.
+OK Welcome to coremail Mail Pop3 Server (dlut.edu.cns[627644c969381353b51c9657b72568a4s])
user xxxxxxxxxx@mail.dlut.edu.cn
+OK core mail
pass xxxxxxxxxx
+OK 4 message(s) [1151199 byte(s)]
list
+OK 4 1151199
1 398270
2 741119
3 1682
4 10128
.
retr 3
+OK 1682 octets
Received: from xxxxxxxxx (unknown [xxxxxxxxx])
        by mx1 (Coremail) with SMTP id UEJ2ygBnb+8toTZjKwx_CA--.36240S2;
        Fri, 30 Sep 2022 15:56:40 +0800 (CST)
hello from linux
X-CM-TRANSID:UEJ2ygBnb+8toTZjKwx_CA--.36240S2
Message-Id:<6336A15F.04A767.07381@dlut.edu.cn>
Authentication-Results: mx1; spf=none smtp.mail=xxx@xxxxxx;
X-Coremail-Antispam: 1UD129KBjDUn29KB7ZKAUJUUUUU529EdanIXcx71UUUUU7v73
        VFW2AGmfu7jjvjm3AaLaJ3UjIYCTnIWjp_UUUrS7k0a2IF6F4UM7kC6x804xWl14x267AK
        xVWUJVW8JwAFIxvE14AKwVWUJVWUGwA2ocxC64kIII0Yj41l84x0c7CEw4AK67xGY2AK02
        1l84ACjcxK6xIIjxv20xvE14v26r1j6r1xM28EF7xvwVC0I7IYx2IY6xkF7I0E14v26r1j
        6r4UM28EF7xvwVC2z280aVAFwI0_Jr0_Gr1l84ACjcxK6I8E87Iv6xkF7I0E14v26r1j6r
        4UM2vYz4IE57IF64kE628EF7xvwwAS0I0E0xvYzxvE52x082IY62kv0487M2AExVAIFx02
        aVAFz4v204v7Mc8Ir4CE8sxKj4xv1VAv77x28xyl52xGzVA2a4k0FcxF6cIjj282cryl5I
        8CrVACY4xI64kE6c02F40Ex7xfMcIj64x0Y40En7xvr7AKxVWUJVW8JwAv7VC0I7IYx2IY
        67AKxVWUtVWrXwAv7VC2z280aVAFwI0_Jr0_Gr1lOx8S6xCaFVCjc4AY6r1j6r4UM4x0Y4
        8IcVAKI48JM4x0aVACjI8F5VA0II8E6IAqYI8I648v4I1lw4AK0VCY07AIYIkI8VC2zVAC
        3wAKzVAC0xCFj2AI6cx7M4kE6I8I3I0E14AKx2xKxVC2ax8xMx02cVCv0xWlc7CjxVAKzI
        0EY4vE52x082I5MxkI7II2jI8vz4vEwIxGrwCYIxAIcVC0I7IYx2IY67AKxVWUJVWUCwCY
        IxAIcVC0I7IYx2IY6xkF7I0E14v26r1j6r4UMxvI42IY6I8E87Iv67AKxVWUJVW8JwCYIx
        AIcVC2z280aVCY1x0267AKxVWUJVW8JwCF04k20xvY0x0EwIxGrwCF04k20xvEw4C26cxK
        6c8Ij28IcwCFw20E84ACjcxK64kEx2IqYxC7MxCjnVAKz4kxMxC20s026xCaFVCjc4AY6r
        1j6r4UMI8I3I0E5I8CrVAFwI0_Jr0_Jr4lx2IqxVCjr7xvwVAFwI0_Jr0_Jr4lx4CE17CE
        b7AF67AKxVWUJVWUXwCI42IY6xAIw20EY4v20xvaj40_Zr0_Wr1UYxBIdaVFxhVjvjDU0x
        ZFpf9x07b6AwxUUUUU=
Date: Fri, 30 Sep 2022 15:57:19 +0800 (CST)
From: xxx@xxxxxx

.
quit
+OK core mail
Connection closed by foreign host.
```

## DNS实验

使用远程 LInux 主机

### 基本介绍

bind是linux系统下的一个DNS服务程序

bind-utils是bind软件提供的一组DNS工具包,可以进行域名解析和DNS调试工作

主要有：dig,host,nslookup,nsupdate

### 安装工具包

Cent OS 使用命令（root用户）

```shell
sudo yum install bind-utils
```

### 使用

nslookup用于查询DNS的记录，输入一个主机名并发现相应的IP地址

```
[user1@qmmms ~]$ nslookup www.baidu.com
Server:         100.125.1.250
Address:        100.125.1.250#53

Non-authoritative answer:
www.baidu.com   canonical name = www.a.shifen.com.
Name:   www.a.shifen.com
Address: 110.242.68.4
Name:   www.a.shifen.com
Address: 110.242.68.3
```

```
[user1@qmmms ~]$ host www.baidu.com
www.baidu.com is an alias for www.a.shifen.com.
www.a.shifen.com has address 110.242.68.3
www.a.shifen.com has address 110.242.68.4
```

```
[user1@qmmms ~]$ dig www.baidu.com

; <<>> DiG 9.11.4-P2-RedHat-9.11.4-26.P2.el7_9.9 <<>> www.baidu.com
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 38365
;; flags: qr rd ra; QUERY: 1, ANSWER: 3, AUTHORITY: 0, ADDITIONAL: 1

;; OPT PSEUDOSECTION:
; EDNS: version: 0, flags:; udp: 4096
;; QUESTION SECTION:
;www.baidu.com.                 IN      A

;; ANSWER SECTION:
www.baidu.com.          399     IN      CNAME   www.a.shifen.com.
www.a.shifen.com.       21      IN      A       110.242.68.3
www.a.shifen.com.       21      IN      A       110.242.68.4

;; Query time: 0 msec
;; SERVER: 100.125.1.250#53(100.125.1.250)
;; WHEN: Mon Oct 03 12:54:30 CST 2022
;; MSG SIZE  rcvd: 101
```

## UDP套接字编程

### 目标

1.   在本地客户端输入一段字符串
2.   发送给服务器
3.   服务器把字符串改为全大写
4.   发送给本地客户端
5.   本地客户端显示修改过的字符串

### 准备

当然要两台电脑，或者虚拟机，或者租一个远程服务器

作者租了一个远程服务器，Linux 系统，提前把 python3 之类的环境配置好

如果远程服务器开了防火墙，记得把相关端口允许放行，或者短暂关闭防火墙

### 客户端代码

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

### 服务器端代码

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

### 运行实例

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

## TCP套接字编程

### 目标

1.   在本地客户端输入一段字符串
2.   发送给服务器
3.   服务器把字符串改为全大写
4.   发送给本地客户端
5.   本地客户端显示修改过的字符串

### 客户端代码

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

### 服务器端代码

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

### 运行实例

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

## WebServer套接字编程作业

### 目标

实现一个 Web 服务器，可以在浏览器上访问

### 代码

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

### 部署

将两个文件都放在远程服务器上，运行 WebServer.py
