# 文件与权限

## 准备工作

------

新增用户与用户组，两个目的

- 使用普通用户登陆系统，避免root误操作
- 便于观察文件权限改变结果

在root下执行以下命令：

```shell
groupadd basic_users
useradd -g basic_users user1
passwd user1
[设置密码......]

useradd qms
passwd qms
[设置密码......]
```

- 更加细节的用户管理之后再讲
- 添加了一个用户组`basic_users`
- 添加了一个用户`user1`，属于用户组`basic_users`
- 添加了一个用户`qms`，系统默认添加用户组`qms`

## 文件属性

------

登陆`user1`，输入命令：

```shell
touch doc
ls -la
```

观察输出：

```
总用量 20
drwx------  2 user1 basic_users 4096 9月   1 17:21 .
drwxr-xr-x. 4 root  root        4096 9月   1 17:22 ..
-rw-r--r--  1 user1 basic_users   18 11月 25 2021 .bash_logout
-rw-r--r--  1 user1 basic_users  193 11月 25 2021 .bash_profile
-rw-r--r--  1 user1 basic_users  231 11月 25 2021 .bashrc
-rw-r--r--  1 user1 basic_users    0 9月   1 17:21 doc
```

每个记录（每一行）有七个信息，分别是：

1. 类型与权限
2. 连接到此节点的文件数量（比如目录下属的文件数量）
3. 拥有者
4. 所属用户组
5. 文件大小（B）
6. 最近修改日期
7. 文件名

关于类型与权限：

- 第一个字符为`d`，代表目录
- 第一个字符为`-`，代表文件
- 之后三个字符为一组，分别为拥有者权限，组成员权限，其他人权限
- `r`代表可读，`w`代表可写，`x`代表可执行，`-`代表没有相应权限
- `root`账号拥有所有权限

**例子：**

```
-rw-r--r--  1 user1 basic_users    0 9月   1 17:21 doc
```

doc是一个文件，拥有者`user1`，所属组`basic_users`

拥有者可读可写，组成员可读，其他人可读

## 修改属性与权限

------

### 修改所属组

**格式：**

```shell
chgrp [-R] 用户组 文件或目录
```

-R代表递归修改（修改目录里面的所有文件）

**例子：**

```shell
chgrp qms doc
```

```
-rw-r--r-- 1 user1 qms 0 9月   1 17:21 doc
```

测试后改回

### 修改文件拥有者

```shell
chown [-R] 用户名 文件或目录
```

用法与`chgrp`类似

### 修改权限

**格式1：**

```shell
chmod [-R] 权限数字 文件或目录
```

- -R代表递归修改（修改目录里面的所有文件）
- 关于权限数字，`r`为4，`w`为2，`x`为1，累加得身份权限，共三个身份

**例子1：**

```shell
chmod 764 doc
```

```
-rwxrw-r--  1 user1 basic_users    0 9月   1 17:21 doc
```

**例子2：**

```shell
chmod 000 doc
chmod a+r doc
```

```
-r--r--r-- 1 user1 basic_users    0 9月   1 17:21 doc
```

- `a`代表所有
- `+`代表添加权限
- `chmod a+r doc`代表给每个身份都添加读权限

**例子3:**

```shell
chmod 777 doc
chmod go-wx,u-x doc
```

```
-rw-r--r-- 1 user1 basic_users    0 9月   1 17:21 doc
```

- `u`代表用户身份，`g`代表组员身份，`o`代表其他人身份
- `-`代表减去权限

## 对权限的理解

------

### 对于文件

- `r`是基本权限，读文件权限
- `w`是对文件内容的操作，不包括对文件本身操作（例如删除文件）
- Linux内可执行文件没有固定的扩展名，而由`x`权限确定

### 对于目录

- `x`是基本权限，是进入目录的权限（专业来讲，是将该目录作为工作目录的权限）
- `r`是可以看到目录内文件名的权限，仅仅而已
- 有`r`无`x`只能看到文件名，其他什么也干不了
- 有`x`无`r`只是看不到文件名，其他什么都能干
- `w`是修改目录结构的权限，包括删除文件（无论文件的权限是什么），添加文件和目录等等
- 如果要开放目录，需要给出`rx`权限，`w`权限不能随意给
