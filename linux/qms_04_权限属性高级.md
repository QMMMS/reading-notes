# 权限属性高级

## 隐藏属性

------

### 查看隐藏属性

**格式：**

```shell
lsattr [参数] 文件或目录
```

**参数：**

- `-a`查看隐藏文件
- `-d`查看目录本身
- `-R`递归查看

### 设置隐藏属性

**格式：**

```shell
chattr [参数] 文件或目录
```

**参数：**

- `+`添加属性
- `-`移除属性
- `=`设置属性
- `a`只能增加数据
- `i`不能删除，改名，设置链接，更改内容

**例子：**

```
[root@qmmms doc]# chattr +i test.txt 
[root@qmmms doc]# lsattr test.txt 
----i--------e-- test.txt
[root@qmmms doc]# rm test.txt 
rm：是否删除普通文件 "test.txt"？y
rm: 无法删除"test.txt": 权限不够
```

- root也无法删除，需要先移除属性

## 特殊权限

------

### SUID

- 如果文件拥有者的权限`x`替代为`s`，则有SUID权限
- SUID只对二进制程序有效
- 在程序执行时，执行者短暂拥有拥有者的权限

**例子：**

```
[user1@qmmms ~]$ ls -l /usr/bin/passwd 
-rwsr-xr-x. 1 root root 27856 4月   1 2020 /usr/bin/passwd
```

- 一般用户不能直接修改密码文件
- `passwd`命令所有者是root
- 一般用户可以使用`passwd`命令，短暂拥有root权限，间接修改密码文件

### SGID

如果文件所属用户组的权限`x`替代为`s`，则有SGID权限，对文件，目录都有效

对文件：

- 只对二进制文件有效
- 在程序执行时，执行者短暂拥有文件所属用户组的权限

对目录：

- 在目录下，用户的有效用户组变成目录的用户组
- 比如其他用户在该目录建立新文件，文件所属用户组为目录的用户组

### SBIT

- 如果相应权限`x`替代为`t`，则有SBIT权限
- 只对目录有效
- 当用户在目录下建立文件或目录，只有root和拥有者可以删除

**例子：**

```
[root@qmmms user1]# mkdir tmp
[root@qmmms user1]# chmod 777 tmp
[root@qmmms user1]# chmod o+t tmp
[root@qmmms user1]# ls -ld tmp
drwxrwxrwt 2 root root 4096 9月   4 23:04 tmp
[root@qmmms user1]# touch tmp/test
[root@qmmms user1]# exit
exit
[user1@qmmms ~]$ rm tmp/test
rm：是否删除有写保护的普通空文件 "tmp/test"？y
rm: 无法删除"tmp/test": 不允许的操作
```

- 即使`tmp`目录权限为777，非创建者依旧无法删除他人文件

### 设置权限

依旧使用`chmod`命令，权限数字改为4个，第一个数字表示特殊权限

- 4 为 SUID
- 2 为 SGID
- 1 为 SBIT

**例子：**

```
[user1@qmmms ~]$ chmod 4755 doc
[user1@qmmms ~]$ ls -l doc
-rwsr-xr-x 1 user1 basic_users 0 9月  12 1998 doc
[user1@qmmms ~]$ chmod 1776 dir_test/
[user1@qmmms ~]$ ls -ld dir_test/
drwxrwxrwT 2 user1 basic_users 4096 9月   2 17:24 dir_test/
```

- 注意大写的T，意思是这个权限实际不存在，因为没有`x`权限，自然没有`t`权限

```
[user1@qmmms ~]$ chmod u=rwxs,go=x doc
[user1@qmmms ~]$ ls -l doc
-rws--x--x 1 user1 basic_users 0 9月  12 1998 doc
[user1@qmmms ~]$ chmod g+s doc
[user1@qmmms ~]$ ls -l doc
-rws--s--x 1 user1 basic_users 0 9月  12 1998 doc
```

## 默认权限

-------

### 查看默认权限

**格式：**

```shell
umask [参数]
```

**参数：**

- 不带参数展示权限**掩码**，意思是要拿掉的权限数字
- `-S`文字展示

### 更改默认权限

**格式：**

```shell
umask 权限数字
```

## 观察文件类型

------

**例子：**

```
[user1@qmmms ~]$ file /usr/bin/passwd
/usr/bin/passwd: setuid ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.32, BuildID[sha1]=dee1b9ab6618c6bfb84a14f85ba258c742cf4aec, stripped
[user1@qmmms ~]$ file ~/.bashrc
/home/user1/.bashrc: ASCII text
```

## ACL使用

------

ACL，中文为**访问控制列表**，可以提供更加细化的权限管理，比如单独设置某一用户的权限

### 设置ACL

**格式：**

```shell
setfacl [参数] 文件或目录
```

**参数：**

- `-m acl参数`：为文件或目录设置acl参数
- `-x acl参数`：去掉acl参数
- `-b`：删除文件或目录的所有acl参数
- `-R`：递归设置acl参数

**acl参数：**

- u:用户:权限
- g:用户组:权限

注：设置完ACL后权限部分会后加一个`+`符号

### 查看ACL

**格式：**

```shell
getfacl 文件或目录
```

**例子：**

```
[user1@qmmms dir_test]$ setfacl -m u:qms:r hello
[user1@qmmms dir_test]$ ll
total 4
-rwxr-----+ 1 user1 basic_users 6 Sep 29 21:41 hello
[user1@qmmms dir_test]$ getfacl hello 
# file: hello
# owner: user1
# group: basic_users
user::rwx
user:qms:r--
group::---
mask::r--
other::---
```
