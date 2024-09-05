# 文件与目录操作

## 目录操作

### 切换目录

```shell
cd ~
cd
```

这两个命令结果相同，前往家目录

```shell
cd ~用户
```

前往目标用户的家目录

```shell
cd -
```

返回上一个进入的目录（`cd ..`到上一层目录）

### 显示当前目录

```shell
pwd -P 
```

对于链接文件，显示正确的完整路径

**例子：**

```
[root@qmmms user1]#  cd /var/mail/
[root@qmmms mail]#  pwd
/var/mail
[root@qmmms mail]#  pwd -P
/var/spool/mail
```

**解释：**

```
[root@qmmms mail]# ls -ld /var/mail
lrwxrwxrwx. 1 root root 10 2月  10 2022 /var/mail -> spool/mail
```

第一个字符为`l`，链接文件，真正路径为`/var/spool/mail`

### 建立新目录

```shell
mkdir -m 权限数字 目录
```

在创建目录时指定权限

```shell
mkdir -p 目录
```

可以创建很多套着的目录

**例子：**

```
[user1@qmmms ~]$ mkdir -p tmp1/tmp2/tmp3
```

## 环境变量PATH

------

- 命令本质是程序，Linux首先到环境变量`PATH`指定的目录寻找相应程序
- 查看`PATH`：`echo $PATH`
- 添加内容：`PATH="${PATH}:新目录"`
- 不同身份的PATH是不同的，所以可执行的命令也不同
- 建议避免将本目录（.）加入`PATH`

**例子：**

在`user1`家目录添加一个C语言文件 sayhi.c，编译，添加`PATH`

```c
#include<stdio.h>
int main(){
	printf("hello world!");
	return 0;
}
```

```
[user1@qmmms ~]$ gcc -o sayhi sayhi.c 
[user1@qmmms ~]$ pwd
/home/user1
[user1@qmmms ~]$ PATH="${PATH}:/home/user1"
[user1@qmmms ~]$ cd /
[user1@qmmms /]$ sayhi 
hello world!
```

之后不管进入哪个目录都能直接运行`sayhi`

补充：可以设置`~/bin`目录，可执行文件可以放在这里，不需要手动设置PATH就可以执行

## 文件与目录管理

------

### 查看目录下文件

**格式：**

```shell
ls [-参数] [目录]
```

**参数：**

- 不写目录则列出本目录下文件
- `-l`列出详细信息
- `-a`列出隐藏文件
- `-d`列出目录本身，而非下属文件
- `--full-time`查看完整时间

**例子：**

```
[user1@qmmms ~]$ ls -ld
drwx------ 3 user1 basic_users 4096 9月   2 13:36 .
[user1@qmmms ~]$ ls -la --full-time
总用量 48
drwx------  3 user1 basic_users 4096 2022-09-02 13:36:40.858009949 +0800 .
drwxr-xr-x. 4 root  root        4096 2022-09-01 17:22:33.807794464 +0800 ..
-rw-------  1 user1 basic_users 2277 2022-09-02 15:48:52.017149895 +0800 .bash_history
-rw-r--r--  1 user1 basic_users   18 2021-11-25 00:33:26.000000000 +0800 .bash_logout
-rw-r--r--  1 user1 basic_users  193 2021-11-25 00:33:26.000000000 +0800 .bash_profile
-rw-r--r--  1 user1 basic_users  231 2021-11-25 00:33:26.000000000 +0800 .bashrc
d--x------  2 user1 basic_users 4096 2022-09-01 22:55:48.476880951 +0800 dir_test
-rw-r--r--  1 user1 basic_users    0 2022-09-01 17:21:36.143959693 +0800 doc
-rwxr-xr-x  1 user1 basic_users 8360 2022-09-02 13:36:40.869010113 +0800 sayhi
-rw-r--r--  1 user1 basic_users   72 2022-09-02 13:36:38.407973465 +0800 sayhi.c
-rw-------  1 user1 basic_users  669 2022-09-02 13:36:38.409973495 +0800 .viminfo
```

### 复制

**格式：**

```shell
cp [参数] 源文件 目标文件
```

**参数：**

- `-a`包括内容，也复制文件所有特性
- `-p`包括内容，也复制文件所有特性
- `-i`覆盖前询问
- `-r`递归复制
- `-s`复制为链接（快捷方式）
- 注：支持操作多文件，最后一个文件一定是目录

**例子：**

```
d--x------ 2 user1 basic_users 4096 9月   1 22:55 dir_test
-rw-r--r-- 1 user1 basic_users    0 9月   1 17:21 doc
-rwxr-xr-x 1 user1 basic_users 8360 9月   2 13:36 sayhi
-rw-r--r-- 1 user1 basic_users   72 9月   2 13:36 sayhi.c
[user1@qmmms ~]$ cp -s sayhi.c sayhi1.c
[user1@qmmms ~]$ cp sayhi1.c sayhi2.c
[user1@qmmms ~]$ cp -s sayhi1.c sayhi3.c
[user1@qmmms ~]$ ls -l
总用量 24
d--x------ 2 user1 basic_users 4096 9月   1 22:55 dir_test
-rw-r--r-- 1 user1 basic_users    0 9月   1 17:21 doc
-rwxr-xr-x 1 user1 basic_users 8360 9月   2 13:36 sayhi
lrwxrwxrwx 1 user1 basic_users    7 9月   2 16:28 sayhi1.c -> sayhi.c
-rw-r--r-- 1 user1 basic_users   72 9月   2 16:28 sayhi2.c
lrwxrwxrwx 1 user1 basic_users    8 9月   2 16:29 sayhi3.c -> sayhi1.c
-rw-r--r-- 1 user1 basic_users   72 9月   2 13:36 sayhi.c
```

**解释：**

- 链接文件复制到新文件，不带`-s`，会复制为普通文件
- 链接文件复制到新文件，带`-s`，会复制为链接文件
- 注：要在某个文件夹内创建链接文件，必须先进入那个文件夹

### 删除

**格式：**

```shell
rm [参数] 文件或目录
```

**参数：**

- `-i`删除前询问
- `-r`递归删除

**例子：**

```
[user1@qmmms dir_test]$ ls -l
总用量 0
-rw-r--r-- 1 user1 basic_users 0 9月   2 17:24 -aaa-
[user1@qmmms dir_test]$ rm -aaa-
rm：无效选项 -- a
Try 'rm ./-aaa-' to remove the file "-aaa-".
Try 'rm --help' for more information.
[user1@qmmms dir_test]$ rm ./-aaa-
[user1@qmmms dir_test]$ ls -l
总用量 0
```

**解释：**对于文件`-aaa-`，直接删除会把它当作参数，应该为`rm ./-aaa-`

### 移动

**格式：**

```shell
mv [参数] 源文件 目标文件
```

**参数：**

- `-i`覆盖前询问
- 注：支持操作多文件，最后一个文件一定是目录
- 注：合理运用，达到剪贴或重命名的效果

### 硬链接与软链接

Linux 链接分两种，一种被称为硬链接（Hard Link），另一种被称为符号链接（Symbolic Link）。默认情况下，**ln** 命令产生硬链接。

**硬连接**

硬连接指通过索引节点来进行连接。

在 Linux 中，多个文件名指向同一索引节点是存在的。比如：A 是 B 的硬链接（A 和 B 都是文件名），则 A 的目录项中的 inode 节点号与 B 的目录项中的 inode 节点号相同，即一个 inode 节点对应两个不同的文件名，两个文件名指向同一个文件。

A 和 B 对文件系统来说是完全平等的。删除其中任何一个都不会影响另外一个的访问。这样硬连接的作用是允许一个文件拥有多个有效路径名，这样用户就可以建立硬连接到重要文件，以防止“误删”的功能。

只有当最后一个连接被删除后，文件的数据块及目录的连接才会被释放。也就是说，文件真正删除的条件是与之相关的所有硬连接文件均被删除。

**软连接**

另外一种连接称之为符号连接（Symbolic Link），也叫软连接。软链接文件有类似于 Windows 的快捷方式。它实际上是一个文本文件，其中包含的有另一文件的位置信息。

比如：A 是 B 的软链接（A 和 B 都是文件名），A 的数据块中存放的只是 B 的路径名。A 和 B 之间是“主从”关系，如果 B 被删除了，A 仍然存在，但指向的是一个无效的链接。

**命令**

```sh
ln f1 f2          #创建f1的一个硬连接文件f2
ln -s f1 f3       #创建f1的一个符号连接文件f3
ls -li            # -i参数显示文件的inode节点信息
```

当删除原始文件 f1 后，硬连接 f2 不受影响，但是符号连接 f3 文件无效。同时删除原文件f1,硬连接f2，整个文件会真正的被删除。

## 查看文件内容

------

### 直接查看

**格式：**

```shell
cat [参数] 文件
```

**参数：**

- `-n`打印出行号，空行也有行号
- `-A`显示特殊字符，例如换行符`$`，[tab]按键为^I
- 注：`cat`从前向后看，`tac`从后向前看

**例子：**

```
[root@qmmms ~]# cat -n /etc/issue
     1	\S
     2	Kernel \r on an \m
     3	
```

```
[root@qmmms ~]# cat -An /etc/man_db.conf | head -n 71 | tail -n 6
    66	MANDB_MAP^I/usr/man^I^I/var/cache/man/fsstnd$
    67	MANDB_MAP^I/usr/share/man^I^I/var/cache/man$
    68	MANDB_MAP^I/usr/local/man^I^I/var/cache/man/oldlocal$
    69	MANDB_MAP^I/usr/local/share/man^I/var/cache/man/local$
    70	MANDB_MAP^I/usr/X11R6/man^I^I/var/cache/man/X11R6$
    71	MANDB_MAP^I/opt/man^I^I/var/cache/man/opt$
```

- 可以看到换行符和表示[tab]的字符
- `head`命令和`tail`命令之后会提到
- 管道操作`|`之后会提到，简单讲就是把`|`前面的内容交给后面的命令继续处理
- `cat -An /etc/man_db.conf | head -n 71 | tail -n 6`意思是截取前71行再保留最后6行

### 可翻页查看

**格式：**

```shell
more 文件
```

**进入阅览后的操作：**

- 空格键：向下翻一页
- Enter：向下一行
- `q`：离开
- `b`：向上翻一页
- `:f`：显示文件名和当前行号
- `/字符串`：查找字符串，重复查找再按`n`

**格式：**

```shell
less 文件
```

- `less`功能比`more`更强大
- `man`命令默认以`less`打开，这里就不再重述

## 数据截取

### 从顶部截取

**格式：**

```shell
head [-n 行数] 文件
```

从顶部截取文件，行数通过参数给出，如果不写默认10行

### 从底部截取

**格式：**

```shell
tail [-n 行数] 文件
```

从底部截取文件，行数通过参数给出，如果不写默认10行

**例子：**

截取文件 */etc/man_db.conf* 的66行到71行，带行号

```
[root@qmmms ~]# cat -An /etc/man_db.conf | head -n 71 | tail -n 6
    66	MANDB_MAP^I/usr/man^I^I/var/cache/man/fsstnd$
    67	MANDB_MAP^I/usr/share/man^I^I/var/cache/man$
    68	MANDB_MAP^I/usr/local/man^I^I/var/cache/man/oldlocal$
    69	MANDB_MAP^I/usr/local/share/man^I/var/cache/man/local$
    70	MANDB_MAP^I/usr/X11R6/man^I^I/var/cache/man/X11R6$
    71	MANDB_MAP^I/opt/man^I^I/var/cache/man/opt$
```

## 打开二进制文件

------

**格式：**

```shell
od [-t 参数] 文件
```

**参数：**

- `c` ASCII字符输出
- `d[size]`使用十进制输出，每个占用`size`Bytes

**例子：**

列出**hello**的ASCII对照

```
[user1@qmmms ~]$ echo hello | od -t dCc
0000000  104  101  108  108  111   10
           h    e    l    l    o   \n
0000006
```

## 文件与时间

------

对于文件，Linux会记录三个时间属性

- 修改时间，mtime，记录最近内容被修改的时间
- 状态时间，ctime，记录最近状态被改变的时间
- 读取时间，atime，记录最近被读取内容的时间

### 查看时间属性

```
[user1@qmmms ~]$ date;ls -l /etc/man_db.conf;ls -l --time=atime /etc/man_db.conf;ls -l --time=ctime /etc/man_db.conf;
2022年 09月 04日 星期日 16:12:09 CST
-rw-r--r--. 1 root root 5171 10月 31 2018 /etc/man_db.conf
-rw-r--r--. 1 root root 5171 9月   4 13:12 /etc/man_db.conf
-rw-r--r--. 1 root root 5171 2月  10 2022 /etc/man_db.conf
```

- 可以用分号连接指令，会一起输出
- `ls -l`默认输出mtime
- 可以通过`--time=[时间]`输出其他时间

### 修改时间属性

**格式：**

```shell
touch [参数] 文件
```

**参数：**

- 如果没有参数，则修改三个时间
- 如果文件不存在，新建文件
- `-a`：仅修改atime为当前时间
- `-m`：仅修改mtime为当前时间
- `-t 时间`使用给定的时间修改，格式为[YYYYMMDDhhmm]

**例子：**

```
[user1@qmmms ~]$ touch -t 199809120000 doc
[user1@qmmms ~]$ ls -l doc
-rw-r--r-- 1 user1 basic_users 0 9月  12 1998 doc
[user1@qmmms ~]$ ls -l --time=ctime doc
-rw-r--r-- 1 user1 basic_users 0 9月   4 16:26 doc
```

- 将`doc`文件的时间修改为1998-09-12 00:00
- 状态时间ctime 不能人为修改

