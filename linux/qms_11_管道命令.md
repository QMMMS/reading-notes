# 管道命令

通俗来讲，就是把前一个命令的标准输出作为后一个命令的标准输入处理，注意：

-   管道命令只会处理标准输出，忽略标准错误输出
-   命令需要有把前一个命令的标准输出作为标准输入的能力，才能使用管道

支持相关功能的命令很多，就只给例子了

## 过滤信息

-----

在`last`命令的输出中，找到带`root`的行，输出前5行

```
[user1@qmmms ~]$ last | grep "root" | head -n 5
root     pts/0        183.210.228.179  Thu Sep  1 23:20 - down   (00:02)    
root     pts/0        183.210.228.179  Thu Sep  1 22:27 - 22:28  (00:01)    
root     pts/0        183.210.228.179  Thu Sep  1 17:13 - 17:19  (00:06)    
root     pts/0        183.210.228.179  Wed Aug 31 23:09 - down   (00:01)    
root     pts/0        183.210.228.179  Wed Aug 31 21:34 - 21:37  (00:03)    
```

在`last`命令的输出中，找到不带`root`的行（`-v`），输出行号（`-n`），输出最后5行

```
[user1@qmmms ~]$ last | grep -nv "root" | tail -n 5
124:reboot   system boot  3.10.0-1160.53.1 Wed Aug 31 13:05 - 23:11  (10:06)    
126:reboot   system boot  3.10.0-1160.53.1 Wed Aug 31 12:57 - 13:03  (00:06)    
138:reboot   system boot  3.10.0-1160.53.1 Wed Aug 31 08:57 - 12:57  (04:00)    
139:
140:wtmp begins Thu Feb 10 15:19:42 2022
```

当然，`grep`命令也支持查找文件内容

```
[user1@qmmms ~]$ grep "int" simple_add.cpp 
int main(){
	int n = 0;
	int num = 0;
```

在`last`命令的输出中，以空格作为分隔符（`-d`）切割，保留第一个位置的信息（`-f`），输出前3行

```
[user1@qmmms ~]$ last | cut -d ' ' -f 1 | head -n 3
user1
user1
user1
```

## 排序

------

在`/etc/passwd`文件内容的输出中，排序，输出前3行

```
[root@qmmms ~]# cat /etc/passwd | sort | head -n 3
adm:x:3:4:adm:/var/adm:/sbin/nologin
bin:x:1:1:bin:/bin:/sbin/nologin
chrony:x:998:996::/var/lib/chrony:/sbin/nologin
```

在`/etc/passwd`文件内容的输出中，以`:`作为分隔符（`-t`），对第三个位置（`-k`）位置的数据排序，不采取默认字符串的排序方式而使用纯数字的排序方式（`-n`），输出前3行

```
[root@qmmms ~]# cat /etc/passwd | sort -t ':' -k 3 -n | head -n 3
root:x:0:0:root:/root:/bin/bash
bin:x:1:1:bin:/bin:/sbin/nologin
daemon:x:2:2:daemon:/sbin:/sbin/nologin
```

## 去重

------

在`last`命令的输出中，以空格作为分隔符（`-d`）切割，保留第一个位置的信息（`-f`），排序，去重，统计个数（`-c`）

```
[root@qmmms ~]# last | cut -d ' ' -f1 | sort | uniq -c
      1 
      1 qms
     14 reboot
     23 root
    102 user1
      1 wtmp
```

## 统计

------

在`/etc/man_db.conf`文件内容的输出中，分别统计行，字数，字符数

```
[user1@qmmms ~]$ cat /etc/man_db.conf | wc
    131     723    5171
```

## 文件分割和拼接

------

将`./services`文件分割为300k的子文件（`-b`），子文件命名为services+其他标识符

注：按照行数划分使用`-l`

```
[user1@qmmms dir_test]$ split -b 300k ./services services
[user1@qmmms dir_test]$ ll
总用量 1312
-rw-r--r-- 1 user1 basic_users 670293 9月  18 10:11 services
-rw-r--r-- 1 user1 basic_users 307200 9月  18 10:12 servicesaa
-rw-r--r-- 1 user1 basic_users 307200 9月  18 10:12 servicesab
-rw-r--r-- 1 user1 basic_users  55893 9月  18 10:12 servicesac
```

再拼接回来，命名为`servicesback`

```
[user1@qmmms dir_test]$ cat servicesa* >> servicesback
[user1@qmmms dir_test]$ ll
总用量 1968
-rw-r--r-- 1 user1 basic_users 670293 9月  18 10:11 services
-rw-r--r-- 1 user1 basic_users 307200 9月  18 10:12 servicesaa
-rw-r--r-- 1 user1 basic_users 307200 9月  18 10:12 servicesab
-rw-r--r-- 1 user1 basic_users  55893 9月  18 10:12 servicesac
-rw-r--r-- 1 user1 basic_users 670293 9月  18 10:12 servicesback
```

