# 用户管理

## 相关文件

------

在使用`ssh`远程登录时，发生的事件：

1. 在`/etc/passwd`中寻找用户名
2. 若没有用户名，退出。
3. 若有用户名，在`/etc/group`读取用户ID（UID），用户组ID（GID）等相关信息
4. 在`/etc/shadow`中核对密码
5. 如果一切OK，进入shell

### /etc/passwd文件

```
[root@qmmms user1]# head -n 4 /etc/passwd
root:x:0:0:root:/root:/bin/bash
bin:x:1:1:bin:/bin:/sbin/nologin
daemon:x:2:2:daemon:/sbin:/sbin/nologin
adm:x:3:4:adm:/var/adm:/sbin/nologin
```

一行代表一个用户，信息用`:`分隔，分别代表：

1. 账号名
2. 密码，但已经迁移到`/etc/shadow`
3. UID
4. GID
5. 信息说明栏
6. 家目录
7. 默认shell

### /etc/shadow文件

```
[root@qmmms user1]# head -n 4 /etc/shadow
root:$6$5gDFheiF$vSo9u.mXhcZhsBov0nicqnboO2mR62waw9ww7QgY/OJBK6XaN9DAvYh3jgA6JYPx7HrsIZfQrRAC5BxiaonR50:19235:0:99999:7:::
bin:*:18353:0:99999:7:::
daemon:*:18353:0:99999:7:::
adm:*:18353:0:99999:7:::
```

1. 账号名
2. 密码，加密后的
3. 最近修改密码的日期
4. 密码修改后还要几天才能修改
5. 密码需要重新修改的天数
6. 在密码需要修改前的警告天数
7. 密码过期后的宽限时间（密码已经过期，可以登录，登录后强制改密）（过期 != 失效）
8. 账号实现日期
9. 保留

### /etc/group文件

```
[root@qmmms ~]# cat /etc/group | head -n 4
root:x:0:
bin:x:1:
daemon:x:2:
sys:x:3:
```

1. 组名
2. 用户组密码，已经迁移到`/etc/gshadow`
3. GID
4. 此用户组支持的用户名称

### /etc/gshadow文件

```
[root@qmmms ~]# cat /etc/gshadow | head -n 4
root:::
bin:::
daemon:::
sys:::
```

1. 组名
2. 密码
3. 用户组管理员账号
4. 此用户组支持的用户名称

## 查询用户信息

------

**格式：**

```shell
id 账号名
```

**例子：**

```
[user1@qmmms ~]$ id user1
uid=1000(user1) gid=1000(basic_users) groups=1000(basic_users)
```

## 新增用户

------

**格式：**

```shell
useradd [参数] 账号名
```

**常用参数：**

- 不加参数，使用默认值新建账号，查看默认值使用`useradd -D`命令
- `-g 初始用户组`：添加初始用户组
- `-G 次要用户组`：添加该账号还可加入的用户组

**新建账号使用的默认值：**

```
[root@qmmms user1]# useradd -D
GROUP=100
HOME=/home
INACTIVE=-1
EXPIRE=
SHELL=/bin/bash
SKEL=/etc/skel
CREATE_MAIL_SPOOL=yes
```

1. 新建账号的初始用户组GID=100，但是CentOS不会参考这个默认值，而是创建一个与账号名一样的用户组

2. 家目录所在目录

3. 密码过期后几天失效，-1代表不失效

4. 账号失效日期

5. 默认shell

6. 生成家目录的参考目录

   ```
   [root@qmmms ~]# cd /etc/skel
   [root@qmmms skel]# ls -la
   total 20
   drwxr-xr-x.  2 root root 4096 Feb 10  2022 .
   drwxr-xr-x. 76 root root 4096 Sep 26 13:29 ..
   -rw-r--r--   1 root root   18 Nov 25  2021 .bash_logout
   -rw-r--r--   1 root root  193 Nov 25  2021 .bash_profile
   -rw-r--r--   1 root root  231 Nov 25  2021 .bashrc
   ```

7. 是否创建mailbox

**注：**

- `useradd -D`展示的数据来自`/etc/default/useradd ` 这个文件
- 关于UID，GID等默认参数，参考`/etc/login.defs` 这个文件

## 设置密码

------

**格式：**

```shell
passwd [--stdin] [账号名]
```

**常用参数：**

- 不加参数，不加用户名，为自己改密
- 加账号名，为他人改密（权限允许时）
- `--stdin`：通过管道设置密码，使用脚本大量创建账号时使用

**显示详细的密码参数：**

```
[root@qmmms skel]# chage -l user1
Last password change                                    : Sep 01, 2022
Password expires                                        : never
Password inactive                                       : never
Account expires                                         : never
Minimum number of days between password change          : 0
Maximum number of days between password change          : 99999
Number of days of warning before password expires       : 7
```

## 修改用户和密码参数

------

请参考书上`useradd`，`passwd`，`chage`，`usermod`等命令，功能很多不一一列举

**如要更改shell，格式为：**

```shell
chsh [参数]
```

**参数：**

- `-l`：列出可用的shell
- `-s shell`：更改自己的shell

注：查看自己正在使用的shell请使用`echo ${SHELL}`

## 删除用户

------

**格式：**

```shell
userdel [参数] 账号名
```

**参数：**

- 处理的文件为
  - 账号密码相关：`/etc/passwd`，`/etc/shadow`
  - 用户组相关：`/etc/group`，`/etc/gshadow`
  - 个人数据相关：`/home/账号名`，`/var/spool/mail/账号名`
- `-r`：连同家目录一起删除

## 新增用户组

------

**格式：**

```shell
groupadd [参数] 用户组名
```

**参数：**

- `-g GID`：使用特点GID新增用户组

## 修改用户组

------

**格式：**

```shell
groupmod [参数] 用户组名
```

**参数：**

- `-g GID`：修改GID数字
- `-n 新用户组名`：改名

## 删除用户组

------

**格式：**

```shell
groupdel 用户组名
```

注意：只有当没有用户将这个用户组作为初始用户组时，才可以删除该用户组

## 设置用户组管理员

------

**root使用命令：**

```shell
gpasswd [参数] 用户组名
```

**参数：**

- 不加参数，为用户组设置密码
- `-A 账号名`：将用户设置为该用户组管理员
- `-M 账号名`：将用户设置为该用户组普通成员

**用户组管理员使用命令：**

```shell
gpasswd [参数] 用户组名
```

**参数：**

- `-a 账号名`：将用户设置为该用户组普通成员
- `-d 账号名`：将用户移出用户组

**例子：**

```
[root@qmmms ~]# groupadd vip_users
[root@qmmms ~]# gpasswd vip_users
Changing the password for group vip_users
New Password: 
Re-enter new password: 
[root@qmmms ~]# gpasswd -A user1 vip_users
[root@qmmms ~]# su user1
[user1@qmmms root]$ gpasswd -a qms vip_users
Adding user qms to group vip_users
[user1@qmmms root]$ su
Password: 
[root@qmmms ~]# groupdel vip_users
```

## 查询登录信息

------

- `last`和`lastlog`命令：查询用户登录的时间
- `who`和`w`命令：查询当前谁在线
