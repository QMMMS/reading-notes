# DNS实验

使用远程 LInux 主机

## 基本介绍

bind是linux系统下的一个DNS服务程序

bind-utils是bind软件提供的一组DNS工具包,可以进行域名解析和DNS调试工作

主要有：dig,host,nslookup,nsupdate

## 安装工具包

Cent OS 使用命令（root用户）

```shell
sudo yum install bind-utils
```

## 使用

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

