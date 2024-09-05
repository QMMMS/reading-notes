# 命令与文件的查找

## 查找脚本文件

------

**格式：**

```shell
which 命令
```

- `which`从`PATH`中寻找命令的具体文件

**例子：**

```
[user1@qmmms ~]$ which cd
/usr/bin/cd
[user1@qmmms ~]$ which which
alias which='alias | /usr/bin/which --tty-only --read-alias --show-dot --show-tilde'
	/usr/bin/alias
	/usr/bin/which
```

## 查找文件：locate命令

------

**格式：**

```shell
locate [参数] 关键字
```

- 通过关键字查找文件
- `locate`命令通过系统存放文件信息的数据库查找，不是物理查找
- 数据库默认一天一更新，所以新建的文件可能找不到
- 要手动更新数据库，输入`updatedb`命令，需要等待数分钟

**参数：**

- `-l 数字`表示输出几行
- `-S`输出`locate`命令使用的数据库信息
- `-i`忽略大小写区别
- `-c`只输出找到的文件数量

**例子：**

如果使用的Cent OS 没有`locate`命令，需要先安装`yum install mlocate`，然后更新数据库`updatedb`

```
[root@qmmms user1]# locate -S
数据库 /var/lib/mlocate/mlocate.db:
	13,698 文件夹
	77,136 文件
	4,422,616 文件名中的字节数
	1,970,704 字节用于存储数据库
[root@qmmms user1]# locate -l 5 passwd
/etc/passwd
/etc/passwd-
/etc/pam.d/passwd
/etc/security/opasswd
/usr/bin/gpasswd
```

## 查找文件：find命令

------

`find`命令功能更多，但直接查找硬件，速度慢

**例子：**

```shell
find / -mtime 0				#查找根目录下近一天内修改过的文件
find /home -user user1		#查找/home下属于user1的文件
find / -nouser				#查找不属于任何人的文件
find / -name passwd			#查找名字为passwd的文件
find / -name "*passwd*"		#关键字搜索
find /run -type f			#查找文件类型为普通文件的文件
find / -perm /700 -exec ls -l {} \;
#查找权限包含700的文件，并且使用ls -l命令列出它们
```

