# 文件压缩和打包

关于压缩的常见扩展名：

- `*.gz`：gzip程序压缩的文件
- `*.bz2`：bzip2程序压缩的文件
- `*.xz`：xz程序压缩的文件

这些命令和程序只能对单一文件压缩与解压，但可以先把一堆文件打包后再压缩

打包文件扩展名：`*.tar`

打包软件`tar`只负责打包，不负责压缩

如果既打包又压缩，扩展名为:

- `*.tar.gz`
- `*.tar.bz2`
- `*.tar.xz`

## gzip压缩命令

------

gzip支持压缩文件为`*.gz`，解压文件`*.gz`，`*.Z`，`*.zip`

**格式：**

```shell
gzip [参数] 文件
```

**参数：**

- 不带参数：压缩
- `-d`：解压
- `-v`：压缩，并展示压缩信息
- 压缩默认会删除原文件，只保留压缩文件
- 要预览压缩文件内容，使用`zcat 文件`命令

**例子：**

```
[user1@qmmms ~]$ gzip -v services
services:	 79.7% -- replaced with services.gz
[user1@qmmms ~]$ ls -l services.gz
-rw-r--r-- 1 user1 basic_users 136088 9月  12 10:46 services.gz
[user1@qmmms ~]$ gzip -d services.gz
```

## zip

压缩一个目录：

```shell
zip -r archive_name.zip directory_to_compress
```

解压一个zip文件：

```shell
unzip archive_name.zip
```

## 其他压缩命令

------

```shell
bzip2 [参数] 文件		#使用bzip2压缩
bzcat 文件			#预览
xz [参数] 文件			#使用xz压缩
xzcat 文件			#预览
```

参数与gzip基本一样，见上

## 打包命令

------

**格式：**

```shell
tar [参数] [cv] [-f 新文件名] 文件		#打包+压缩
tar [参数] [tv] [-f 包]				#预览包内内容
tar [参数] [xv] [-f 包] [-C 目录]		#解压
```

**参数：**

- `-c`：打包
- `-t`：预览
- `-x`：解压

以上三个命令不能同时出现，可以搭配`-v`实时查看处理的文件名

- `-z`：使用gzip
- `-j`：使用bzip2
- `-J`：使用xz

以上三个命令不能同时出现，注意扩展名配套

- `-C`：解压时表示目标目录
- `-p`：保留原本权限和属性
- `-P`：保留根目录

**例子：**

```
[root@qmmms home]# tar -zcv -f user1.tar.gz user1/
user1/
user1/services
user1/.viminfo
user1/tmp/
user1/tmp/test
user1/.lesshst
user1/.bash_logout
user1/dir_test/
user1/sayhi
user1/.bash_profile
user1/.bash_history
user1/doc
user1/.bashrc
[root@qmmms home]# tar -ztv -f user1.tar.gz 
drwx------ user1/basic_users 0 2022-09-12 11:33 user1/
-rw-r--r-- user1/basic_users 670293 2022-09-12 10:46 user1/services
-rw------- user1/basic_users    805 2022-09-12 10:44 user1/.viminfo
drwxrwxrwt root/root              0 2022-09-04 23:05 user1/tmp/
-rw-r--r-- root/root              0 2022-09-04 23:05 user1/tmp/test
-rw------- user1/basic_users     45 2022-09-04 13:20 user1/.lesshst
-rw-r--r-- user1/basic_users     18 2021-11-25 00:33 user1/.bash_logout
drwxrwxrwT user1/basic_users      0 2022-09-02 17:24 user1/dir_test/
-rwxr-xr-x user1/basic_users   8360 2022-09-02 13:36 user1/sayhi
-rw-r--r-- user1/basic_users    193 2021-11-25 00:33 user1/.bash_profile
-rw------- user1/basic_users   8916 2022-09-12 11:33 user1/.bash_history
-rw------- user1/basic_users     12 2022-09-12 10:44 user1/doc
-rw-r--r-- user1/basic_users    231 2021-11-25 00:33 user1/.bashrc
[root@qmmms home]# tar -zxv -f user1.tar.gz -C ~
user1/
user1/services
user1/.viminfo
user1/tmp/
user1/tmp/test
user1/.lesshst
user1/.bash_logout
user1/dir_test/
user1/sayhi
user1/.bash_profile
user1/.bash_history
user1/doc
user1/.bashrc
```

