# 常用命令

## 下载网络文件

wget是linux下一个从网络上自动下载文件的常用自由工具。它支持HTTP，HTTPS和FTP协议，可以使用HTTP代理。一般的使用方法例如：

```shell
wget http://www.linuxsense.org/xxxx/xxx.tar.gz
```

-c参数, 这个也非常常见, 可以断点续传, 如果不小心终止了, 可以继续使用命令接着下载，例如：

```shell
wget -c http://www.linuxsense.org/xxxx/xxx.tar.gz
```

-P：保存文件之前先创建指定名称的目录。

```shell
wget -P /home/myfile  http://releases.ubuntu.com/18.04/ubuntu-18.04.5-desktop-amd64.iso
```

-O：下载并自定义文件名保存。

```shell
wget -O wordpress.zip http://www.centos.bz/download.php?id=1080 
```

-b：后台下载

```shell
wget -b http://releases.ubuntu.com/18.04/ubuntu-18.04.5-desktop-amd64.iso
Continuing in background, pid 1840. 
Output will be written to `wget-log’. 
```

可以使用以下命令来察看下载进度：

```shell
tail -f wget-log
```

## curl

语法：`curl [option] [url]`

常见选项：

```bash
-b/--cookie <name=string/file>    	 cookie字符串或文件读取位置
-c/--cookie-jar <file>               操作结束后把cookie写入到这个文件中
-C/--continue-at <offset>            断点续转
-o/--output                          把输出写到该文件中
-O/--remote-name                     把输出写到该文件中，保留远程文件的文件名
-#/--progress-bar                    进度条显示当前的传送状态
```

使用示例：

```bash
curl http://www.baidu.com
curl -O http://www.baidu.com/hello.sh
curl -# -o baidu.html http://www.baidu.com
curl http://www.baidu.com -c cookie.txt
curl http://www.baidu.com -b cookie.txt
```

因为服务器没有可视化的浏览器界面，如果一些数据需要登录才能下载，会很麻烦。解决方法是在本地浏览器上把cookie找出来（Chrome浏览器按 F12 + 应用 + 存储 + cookie）。有的时候 cookie 很多需要清洗成固定的格式（`key1=val1;key2=val2`）可以自己写个小程序来清洗：

```python
import os
with open('cookie1.txt', 'r', encoding='utf-8') as f:  # 待清洗
    with open('cookie.txt', 'w', encoding='utf-8') as f2:  # 清洗后
        for line in f:
            line = line.strip()
            parts = line.split()
            print(parts[0], parts[1])
            f2.write(parts[0] + '=' + parts[1] + ';')
```

然后使用 curl -b 选项在服务器上下载数据。

```bash
curl -b "。。。。。" -O https://physionet.org/content/mimiciii/1.4/ADMISSIONS.csv.gz -#
```

## nohup

`nohup` 是一个在 Unix 和类 Unix 操作系统上用来忽略挂断信号，从而让程序在后台持续运行的命令。它的名称代表"no hang up"（不挂起）。

使用 `nohup` 的基本语法如下：

```
nohup command [arg ...] &
```

其中，`command` 是你要运行的命令，`arg` 是命令的参数。`&` 符号表示将命令放入后台执行。

例如，要在后台运行一个长时间执行的脚本文件 `script.sh`，你可以这样使用 `nohup`：

```
nohup ./script.sh &
```

这将使 `script.sh` 在后台运行，并且不受挂断信号的影响。执行后，`nohup` 会在当前目录下生成一个名为 `nohup.out` 的文件，用于存储命令的输出。

- 查看上一个命令的进程号：`echo $!`
- 查看后台运行程序：`ps aux`

## Screen

与nohup类似，可以长时间运行程序，但是提供了更多的灵活度。例如，可以随时返回与程序交互

- **创建新会话**：`screen -S <session_name>`
- **分离当前会话**：`Ctrl+A` 然后 `D`
- **列出所有会话**：`screen -ls`
- **恢复会话**：`screen -r <session_name or PID>`
- **强制踢掉前一个用户连接会话**：`screen -D -r <session_name or PID>`
- **彻底终止会话**：重连进去，`Ctrl+C`停掉程序，然后输入`exit`

## Anaconda 

Anaconda 是一个用于科学计算的 Python 发行版，支持 Linux, Mac, Windows, 包含了众多流行的科学计算、数据分析的 Python 包。

> 类似于Ubuntu是Linux的发行版，你基本不会直接去使用Linux，而是选择一个发行版，如Ubuntu/CentOS/RedHat/Debian等，因为发行版已经提供了基础的组件、库和应用，使用非常简单方便。
>
> 所以，想要学习Python的同学，不要再纠结python2/python3等种种版本了，也不要再纠结各种包的管理和代码移植性问题了。这些统统交给Anaconda。

Miniconda和Anaconda都是基于Conda的包管理器和环境管理系统，它们之间的主要区别在于规模和默认安装内容。

- Miniconda是一个精简版的发行版，只包含了Conda和必要的系统依赖项。它的下载文件相对较小，安装后只有基本的功能，用户可以根据需要手动安装所需的软件包和工具。
- Anaconda则是一个完整的发行版，除了Conda和系统依赖项外，还包括了大量的预安装软件包、库和工具，例如Python解释器、科学计算库（如NumPy、SciPy）、数据处理工具、图形界面等。Anaconda的下载文件较大，安装后直接获得了广泛使用的科学计算和数据分析所需的资源。

Anaconda 安装包下载地址：https://www.anaconda.com/download。[Linux安装conda命令](https://docs.anaconda.com/free/anaconda/install/linux/)

查看 conda 版本：`conda --version`

基本命令：

- 根据`requirements.txt `创建环境`conda create --name <env> --file requirements.txt`
- 创建名字是`MulEHR `的conda环境：`conda create -n MulEHR python=3.8`
- 配置和初始化bash，通常在创建后，激活前完成，初始化要重新启动shell`source ~/.bashrc`：`conda init bash`
- 激活环境：`conda activate MulEHR `
- 要退出当前环境：`conda deactivate`
- 查看所有环境：`conda env list`
- 复制环境：`conda create --name myclone --clone myenv`
- 指定位置创建环境：`conda create -p /dev/conda_envs/new_env python=3.12`
- 删除环境：`conda env remove --name myenv`

> 在较新版本的Conda中，`source activate`和`conda activate`两者实际上是等效的，都用于激活环境。`source activate`是在较早的Conda版本中使用的语法，而`conda activate`是在更新的版本中引入的新语法，目的是更加简洁和一致。因此，在使用最新版本的Conda时，建议使用`conda activate`命令。

如果 `conda create` 有http连接失败，修改`~/.condarc`，改为以下内容：

```
channels:
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/msys2/
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/pro/
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/r/
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/
  - defaults
show_channel_urls: true
```

在使用conda环境时，通常情况下，使用pip安装的包会安装在当前活动的conda环境中，而不会影响其他环境。每个conda环境都有自己独立的包安装路径和环境变量，因此在一个环境中安装的包不会对其他环境产生影响。

## ssh

```bash
ssh-keygen -t rsa -f ~/.ssh/yourname.id_rsa
vi ~/.ssh/config
cat /home/work/.ssh/yourname.id_rsa.pub
```

## 服务器信息

- 版本：cat /etc/issue 
- gpu：nvidia-smi 、nvitop
- cpu：cat /proc/cpuinfo | grep name | cut -f2 -d: |uniq -c 
- 内存：free -h 
- 磁盘：df -h 

## 其他

- 端口占用：netstat -tlnp|grep 端口号 
- 最近某条命令：history |tail -100|grep "git push" 
- 查看防火墙状态： systemctl status firewalld 
- 递归查找文件：find /path/to/search -name "filename"
- 在文件夹内，在特定深度下，统计文件大小：`du -h --max-depth=N 目录名称`

