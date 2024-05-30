# telnet 与 HTTP 实验

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
