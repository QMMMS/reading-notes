# 用户间交流

## 用户对谈

------

如果对方在线（可以用`who`命令查询）且想要传消息给他

```shell
whrie 用户名
```

按回车后执行命令，然后输入具体的信息，按[Ctrl+d]结束输入

**例子**

```
[user1@qmmms ~]$ who
user1    pts/0        2022-09-29 22:26 (210.30.107.27)
qms      pts/1        2022-09-29 22:27 (210.30.107.27)
[user1@qmmms ~]$ write qms
hello qms
welcome!
```

同时在用户qms的终端上显示：

```
[qms@qmmms ~]$ 
Message from user1@qmmms on pts/0 at 22:27 ...
hello qms
welcome!
EOF
```

## 屏蔽消息

------

如果接收者接收了一个消息，那么他正在执行的任务会中断

想要屏蔽所有人的消息（root除外），使用命令`mesg n`

重新启用消息，使用命令：`mesg y`

查看当前的屏蔽设置：`mesg`

## 广播消息

------

**例子：**

```
[qms@qmmms ~]$ wall "welcome to qmmms's linux"
[qms@qmmms ~]$ 
Broadcast message from qms@qmmms (pts/1) (Thu Sep 29 22:37:01 2022):

welcome to qmmms's linux
```

## 查看邮件

------

用户间对谈只适用于双方都在线的情况，想要在对方离线时传达消息，试试mail邮箱

使用`mail`命令进入邮箱，进入后`&`为提示符，具体操作为：

- `?`：查看帮助
- `h 邮件编号`：查看目标邮件编号左右的标题
- `n 邮件编号`：读邮件
- `unread 邮件编号`：将邮件设为未读
- `d 邮件编号`：删除邮件，支持范围删除（`d 30-50`）
- `s 邮件编号 文件`：将邮件保存为文件
- `x`：不保存退出mail，意思是这次对mail的操作不会生效
- `q`：保存并退出mail，这次对mail的操作会生效

```
[root@qmmms ~]# mail
Heirloom Mail version 12.5 7/5/10.  Type ? for help.
"/var/spool/mail/root": 1 message 1 new
>N  1 user1@qmmms.localdom  Fri Sep 16 22:46  16/623   "*** SECURITY information for qmm"
& n 1
Message  1:
From root@qmmms.localdomain  Fri Sep 16 22:46:28 2022
Return-Path: <root@qmmms.localdomain>
X-Original-To: root
Delivered-To: root@qmmms.localdomain
To: root@qmmms.localdomain
From: user1@qmmms.localdomain
Auto-Submitted: auto-generated
Subject: *** SECURITY information for qmmms ***
Date: Fri, 16 Sep 2022 22:46:27 +0800 (CST)
Status: RO

qmmms : Sep 16 22:46:27 : user1 : user NOT in sudoers ; TTY=pts/0 ; PWD=/home/user1 ; USER=root ; COMMAND=apt install sl
```

## 发送邮件

------

```shell
mail -s "标题" 用户名@主机
```

按回车后编辑邮件具体信息，最后一行键入`.`作为结束

如果给同主机用户发送邮件，可以省略`@主机`

当然，可以先编辑好邮件具体信息，通过重定向`<`或管道命令传给`mail`命令，见例子

```
[user1@qmmms ~]$ mail -s "hello root" root
hello
I want to replace you
.
EOT
[user1@qmmms ~]$ ll | mail -s "my home" root
[user1@qmmms ~]$ mail -s "my bashrc" root < ~/.bashrc 
```

