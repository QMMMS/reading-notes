# 命令补充

## 命令别名

------

### 查看命令别名

**格式：**

```shell
alias
```

### 添加命令别名

**格式：**

```shell
alias 别名='命令'
```

**例子：**

```
[user1@qmmms ~]$ alias lm='ls -la | more'
[user1@qmmms ~]$ alias
alias egrep='egrep --color=auto'
alias fgrep='fgrep --color=auto'
alias grep='grep --color=auto'
alias l.='ls -d .* --color=auto'
alias ll='ls -l --color=auto'
alias lm='ls -la | more'
alias ls='ls --color=auto'
alias vi='vim'
alias which='alias | /usr/bin/which --tty-only --read-alias --show-dot --show-tilde'
```

### 删除命令别名

**格式：**

```shell
unalias 别名
```

### 补充：永久化别名

在mac上使用别名时，退出终端后alias列表会重置，如果不想每次设置，下面为设置方法：

1.   切换到用户主目录，命令`cd`
2.   编辑或新建`.bash_profile`文件
3.   在`.bash_profile`文件加上一行：`alias la='ls -a'`
4.   重载该配置文件，命令`source .bash_profile`
5.   如果使用`zsh`，还要设置自动加载`.bash_profile`，在用户主目录编辑`.zshrc`文件，加上一行：`source ~/.bash_profile`
6.   检查当前所有别名设置，命令`alias`

## 历史命令

------

-   bash 会自动记录输入过的命令，比如按上方向键就可以出现上一条命令
-   在登陆主机后，系统从`~/.bash_history`这个文件读取之前执行的命令
-   注销时，才会更新`~/.bash_history`这个文件
-   可以手动更新，下面会提到`-w`参数

### 查看历史命令

**格式：**

```shell
history [参数]
```

**参数：**

-   不加参数列出历史命令
-   `n`：列出最近n个命令
-   `-c`：清除目前shell中的历史命令，安全考虑
-   `-w`：手动更新`~/.bash_history`文件

**例子：**

```
[user1@qmmms ~]$ history 5
  570  2022-09-16 18:15:18 user1 exit
  571  2022-09-16 18:49:41 user1 ls -la
  572  2022-09-16 18:49:51 user1 cat .bash_history 
  573  2022-09-16 18:49:58 user1 exit
  574  2022-09-16 18:56:36 user1 history 5
```

### 相关功能

-   `! 数字`：执行第几条命令
-   `! 开头关键字`：通过开头关键字查找历史命令并执行
-   `!!`：执行上一条命令

**例子：**

```
[user1@qmmms ~]$ history 5
  581  2022-09-16 19:13:13 user1 history 
  582  2022-09-16 19:13:21 user1 cat .bash_history 
  583  2022-09-16 19:13:24 user1 ll
  584  2022-09-16 19:13:27 user1 ls
  585  2022-09-16 19:13:31 user1 history 5
[user1@qmmms ~]$ !!
history 5
  581  2022-09-16 19:13:13 user1 history 
  582  2022-09-16 19:13:21 user1 cat .bash_history 
  583  2022-09-16 19:13:24 user1 ll
  584  2022-09-16 19:13:27 user1 ls
  585  2022-09-16 19:13:31 user1 history 5
[user1@qmmms ~]$ !584
ls
dir_test  doc  lucas.cpp  sayhi  services  tmp
[user1@qmmms ~]$ !ca
cat .bash_history 
```

## 命令执行的判断依据

------

如果多个命令想要一行输入，试试`;`，`&&`，`||` 这三个符号

| 符号 |                         说明                         |
| :--: | :--------------------------------------------------: |
|  ;   |                不考虑前后命令的相关性                |
|  &&  |    若前一个命令执行成功，则执行下一个，反之不执行    |
| \|\| | 若前一个命令执行**不**成功，则执行下一个，反之不执行 |

**例子：**

```
[root@qmmms user1]# sync;sync;sync;shutdown -h +1
Shutdown scheduled for 六 2022-09-17 18:57:36 CST, use 'shutdown -c' to cancel.
```

```
[user1@qmmms ~]$ ls ~/bin && cd ~/bin
ls: 无法访问/home/user1/bin: 没有那个文件或目录
```

```
[user1@qmmms ~]$ ls ~/bin || mkdir ~/bin
ls: 无法访问/home/user1/bin: 没有那个文件或目录
[user1@qmmms ~]$ ls -ld ~/bin
drwxr-xr-x 2 user1 basic_users 4096 9月  17 18:57 /home/user1/bin
```

