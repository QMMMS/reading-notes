# shell变量

## 变量查看

------

**格式：**

```shell
echo ${变量}
```

**例子：**

```
[user1@qmmms ~]$ echo ${PATH}
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/user1/.local/bin:/home/user1/bin
```

## 变量设置与规则

------

直接看例子

```
[user1@qmmms ~]$ qmmms=666
[user1@qmmms ~]$ echo ${qmmms}
666
```

- 要新建变量，直接用`=`赋值
- 变量名由英文字母加数字构成，数字不能开头
- 建议用小写来表示自定义变量，大写是系统的变量

```
[user1@qmmms ~]$ qmmms="qms's name"
[user1@qmmms ~]$ echo ${qmmms}
qms's name
[user1@qmmms ~]$ qmmms=qms\'s\ name
[user1@qmmms ~]$ echo ${qmmms}
qms's name
```

- 要在变量里面用特殊字符，可以用双引号，或者转义字符`\`

```
[user1@qmmms ~]$ lan="lang is $LANG"
[user1@qmmms ~]$ echo ${lan}
lang is zh_CN.UTF-8
[user1@qmmms ~]$ lan='lang is $LANG'
[user1@qmmms ~]$ echo ${lan}
lang is $LANG
```

- 双引号内可以表示变量
- 单引号保留纯文本

```
[user1@qmmms ~]$ ver="version is $(uname -r)"
[user1@qmmms ~]$ echo ${ver}
version is 3.10.0-1160.53.1.el7.x86_64
```

- 使用`$(命令)`可以先执行命令，得到输出文本并使用，用 \` 就行

## 变量修改

------

### 增添内容

**格式：**

```shell
变量=${变量}新内容
```

**例子：**

```
[user1@qmmms ~]$ echo ${PATH}
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/user1/.local/bin:/home/user1/bin
[user1@qmmms ~]$ PATH=${PATH}:/home/user1
[user1@qmmms ~]$ echo ${PATH}
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/user1/.local/bin:/home/user1/bin:/home/user1
```

### 删除部分内容

**格式：**

- `${变量#关键词}`：从**头**搜索，删除符合的最**短**数据
- `${变量##关键词}`：从**头**搜索，删除符合的最**长**数据
- `${变量%关键词}`：从**尾**搜索，删除符合的最**短**数据
- `${变量%%关键词}`：从**尾**搜索，删除符合的最**长**数据

**例子：**

```
[user1@qmmms ~]$ path=${PATH}
[user1@qmmms ~]$ echo ${path}
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/user1/.local/bin:/home/user1/bin
[user1@qmmms ~]$ echo ${path#/*:}
/usr/bin:/usr/local/sbin:/usr/sbin:/home/user1/.local/bin:/home/user1/bin
[user1@qmmms ~]$ echo ${path##/*:}
/home/user1/bin
[user1@qmmms ~]$ echo ${path%/*}
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/user1/.local/bin:/home/user1
[user1@qmmms ~]$ echo ${path%%/*}

```

- 注意最后一行全空，因为全删了

### 替换内容

**格式：**

- `${变量/旧字符串/新字符串}`：找到**第一个**旧字符串并替换
- `${变量//旧字符串/新字符串}`：找到第**所有**旧字符串并替换

**例子：**

```
[user1@qmmms ~]$ path=${PATH}
[user1@qmmms ~]$ echo ${path}
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/user1/.local/bin:/home/user1/bin
[user1@qmmms ~]$ echo ${path/bin/BIIIN}
/usr/local/BIIIN:/usr/bin:/usr/local/sbin:/usr/sbin:/home/user1/.local/bin:/home/user1/bin
[user1@qmmms ~]$ echo ${path//bin/BIIIN}
/usr/local/BIIIN:/usr/BIIIN:/usr/local/sBIIIN:/usr/sBIIIN:/home/user1/.local/BIIIN:/home/user1/BIIIN
```

### 取消变量

**格式：**

```shell
unset 变量
```

## 特殊变量

------

-   PATH：之前提过，执行命令的查找目录
-   PS1：命令提示字符格式
-   $：当前shell的 PID
-   ？：上个执行命令的返回值，成功为 0
-   SHELL：当前shell是哪个程序
-   HOME：家目录
-   LANG：语系

```
[user1@qmmms ~]$ echo $PS1
[\u@\h \W]\$
[user1@qmmms ~]$ echo $$
1521
[user1@qmmms ~]$ echo $?
0
[user1@qmmms ~]$ echo $SHELL
/bin/bash
[user1@qmmms ~]$ echo $HOME
/home/user1
[user1@qmmms ~]$ echo $LANG
zh_CN.UTF-8
```

## 变量的有效范围

------

对于自定义的变量或者手动修改过的环境变量，在下一次启动shell的时候会失效

因为在启动shell时，操作系统重新分配环境变量

如果想要每次启动shell都自动加载之前的设置，可以编辑家目录下的`.bashrc`文件，是用户登录时执行的脚本文件。该文件本身包含终端会话的一系列配置。 这包括设置或启用：着色，完成，shell历史记录，命令别名等。

父shell的自定义变量无法在子shell中生效（使用命令`bash`启动子shell），原因一样

不过可以使用命令`export 变量`使变量在子shell中生效

```
[user1@qmmms ~]$ myName=QMMMS
[user1@qmmms ~]$ export myName
[user1@qmmms ~]$ bash
[user1@qmmms ~]$ echo ${myName}
QMMMS
```

## 键盘输入变量

-------

**格式：**

```shell
read [参数] 变量
```

**参数：**

-   `-p`：后接提示字符
-   `-t`：限制等待秒数

**例子：**

```
[user1@qmmms ~]$ read -p "type your name : " -t 30 myName
type your name : QMMMS
[user1@qmmms ~]$ echo ${myName}
QMMMS
[user1@qmmms ~]$ read -p "type your name : " -t 1 myName
type your name : [user1@qmmms ~]$ 
```

## 声明变量类型

------

**格式：**

```shell
declare [参数] 变量
```

**参数：**

-   `-a`：声明为数组
-   `-i`：声明为整数
-   `-r`：只读变量，不可修改或删除变量
-   以上三个，对应`+参数`可以取消对应类型
-   `-p`：列出类型

**例子：**

```
[user1@qmmms ~]$ ans=1+2
[user1@qmmms ~]$ echo ${ans}
1+2
[user1@qmmms ~]$ declare -i ans
[user1@qmmms ~]$ ans=1+2
[user1@qmmms ~]$ echo ${ans}
3
[user1@qmmms ~]$ declare -r ans
[user1@qmmms ~]$ unset ans
-bash: unset: ans: 无法反设定: 只读 variable
[user1@qmmms ~]$ declare -p ans
declare -ir ans="3"
```

```
[user1@qmmms ~]$ declare -a var
[user1@qmmms ~]$ var[1]=hello
[user1@qmmms ~]$ var[2]=linux
[user1@qmmms ~]$ echo ${var[1]}
hello
[user1@qmmms ~]$ echo ${var[2]}
linux
```

