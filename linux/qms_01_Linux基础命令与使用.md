# Linux基础命令与使用

## 基础命令

------

- `ls`查看当前目录内容
- `ls -la`查看当前目录详细内容，包括隐藏文件
- `pwd`查看当前所在文件位置
- `cd 文件夹` 进入文件夹
- `cd ..`退回上层文件夹
- `cat 文件`查看文件内容
- `touch 文件`创建文件
- `rm 文件`删除文件
- `cp 源文件 目标文件`复制文件
- `mkdir 文件夹`创建文件夹
- `rm -r 文件夹`删除文件夹
- `date`时间
- `cal [-月] [-年]`日历
- `bc`简单计算器

## 重要热键

------

- [tab]按键：补全指令或文件名
- [Ctrl]-c按键：中断目前程序
- [Ctrl]-d按键：文件结束符EOF

## 寻求帮助

------

只要记住重要命令，其余可以在用指令查具体用法

```shell
指令 --help
```

--help 会提供简要的帮助信息

```shell
man 指令
```

```
info 指令
```

`man`、`info`会提供详细的帮助手册，按`q`退出，具体使用方法见手册内帮助

此外，可以进入/usr/share/doc查看文档

## 文本编辑

先不用更强大的vim，这里用nano

如果没有安装，CentOS需要执行

```shell
yum -y install nano
```

开始编辑，输入命令

```shell
nano test.txt
```

显示编辑页面，可以开始编辑

```
  GNU nano 2.3.1                文件： test.txt                            已更改  

a file edited by nano







                                    [ 新文件 ]
^G 求助      ^O 写入	  ^R 读档      ^Y 上页      ^K 剪切文字  ^C 游标位置
^X 离开      ^J 对齐	  ^W 搜索      ^V 下页      ^U 还原剪切  ^T 拼写检查
```

功能可以在页面下方找到，常用的有

- [Ctrl]-o：保存
- [Ctrl]-x：离开

## 重启与关机

------

### 准备工作

Linux是多用户系统，在重启或关机前要查看系统使用状态并准备，常用命令如下

- `who`查看目前谁在线
- `netstat -a`查看网络联机状态
- `ps`查看正在执行的程序
- `ps -aux`查看执行的程序，包括后台程序
- `sync`将内存中的数据写入磁盘

### 重启

```shell
reboot
```

### 关机

格式：

```shell
shutdown [参数] [时间] [警告信息]
```

例子：

```shell
shutdown -h now 
```

- `-h`代表系统服务停止后立即关机
- `now` 代表现在关机

```shell
shutdown -r +30 "system will reboot after 30min"
```

- `-r`代表系统服务停止后重新启动
- `+30`代表30分钟后执行
- 最后的信息会广播给所有用户

```shell
shutdown -k 20:30 "system will reboot at 20:30"  
```

- `-k`只是广播信息，不会真关机
- `20:30`表示下一个20:30关机

```shell
shutdown -c
```

- 取消预定的关机操作