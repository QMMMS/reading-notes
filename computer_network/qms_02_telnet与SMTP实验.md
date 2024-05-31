# telnet 与 SMTP 实验

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
