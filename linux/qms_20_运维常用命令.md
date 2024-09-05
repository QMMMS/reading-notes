# 运维常用命令

查看指定（例如9030）端口是否被监听

```bash
netstat -nltp |grep 9030
```

查看某个端口/服务相关进程

```bash
ps -ef |grep 9030
```

在B机器查看是否可以访问A机器某个端口,查看端口是否开放

```bash
telnet A服务器IP A服务器端口
```

查看端口占用列表

```bash
netstat -ntulp
```

查看端口占用情况 

```bash
lsof -i :80
```

查看哪些进程监听了2181端口

```cs
netstat -nap |grep 2181 | awk '{print $7}' | sort
```

查看已删除却没有释放的进程

```bash
lsof -n / |grep deleted
```

查看cpu占用前10行情况

```bash
ps -aux --sort=-pcpu|head -10
```

查看服务器内存占用前十行相关进程

```bash
ps -aux | sort -k4nr | head -10
ps -eo pmem,pcpu,rss,vsize,args | sort -k 1 -r | less
```

查看TCP请求中各个状态的数据,如timewait

```bash
netstat -n | awk '/^tcp/ {++S[$NF]} END {for(a in S) print a, S[a]}';netstat -nat |wc -l
```

启动docker所有容器

```bash
docker start $(docker ps -a | awk '{ print $1}' | tail -n +2)
```

查看当前目录下文件夹的大小,1代表第一层

```bash
sudo du -h --max-depth=1
sudo du -h --max-depth=1 --exclude='./data' --exclude='./mnt' --exclude='./proc'
```

查询大于100M的文件

```bash
find / -type f -size +100000k -ls
```

查看最近两个小时生成的文件

```bash
find / -iname "*" -amin 120 -type f
```

删除指定目录下大于指定天数的日志

```bash
cd "/data/bigdata/download/"  && ls -tF |grep '/$'|awk '{if (NR > 3) print $0 }'|xargs rm -rf
```

查看有多少远程IP在连接本机

```bash
netstat -atn  |  awk  '{print $5}'  | awk  '{print $1}' | sort -nr  |  uniq -c
```

统计当前 Linux 系统中可以登录计算机的账户有多少个

```bash
grep "bash$" /etc/passwd | wc -l
```

实时监控本机内存和硬盘剩余空间，剩余内存小于500M、根分区剩余空间小于1000M时，发送报警邮件给root管理员

```bash
#!/bin/bash
 
# 实时监控本机内存和硬盘剩余空间,剩余内存小于500M、根分区剩余空间小于1000M时,发送报警邮件给root管理员
 
# 提取根分区剩余空间
disk_size=$(df / | awk '/\//{print $4}')
 
# 提取内存剩余空空间
mem_size=$(free | awk '/Mem/{print $4}')
while :
do 
# 注意内存和磁盘提取的空间大小都是以 Kb 为单位
if  [  $disk_size -le 512000 -a $mem_size -le 1024000  ]
then
    mail  ‐s  "Warning"  root  <<EOF
 Insufficient resources,资源不足
EOF
fi
done
```

根据PID过滤进程所有信息

```bash
#!/bin/bash
# Function: 根据用户输入的PID，过滤出该PID所有的信息
read -p "请输入要查询的PID: " P
n=`ps -aux| awk '$2~/^'$P'$/{print $11}'|wc -l`
if [ $n -eq 0 ];then
 echo "该PID不存在！！"
 exit
fi
echo "--------------------------------"
echo "进程PID: $P"
echo "进程命令：`ps -aux| awk '$2~/^'$P'$/{print $11}'`"
echo "进程所属用户: `ps -aux| awk '$2~/^'$P'$/{print $1}'`"
echo "CPU占用率：`ps -aux| awk '$2~/^'$P'$/{print $3}'`%"
echo "内存占用率：`ps -aux| awk '$2~/^'$P'$/{print $4}'`%"
echo "进程开始运行的时刻：`ps -aux| awk '$2~/^'$P'$/{print $9}'`"
echo "进程运行的时间：`ps -aux| awk '$2~/^'$P'$/{print $10}'`"
echo "进程状态：`ps -aux| awk '$2~/^'$P'$/{print $8}'`"
echo "进程虚拟内存：`ps -aux| awk '$2~/^'$P'$/{print $5}'`"
echo "进程共享内存：`ps -aux| awk '$2~/^'$P'$/{print $6}'`"
echo "--------------------------------"
```

根据进程名过滤进程信息

```bash
#!/bin/bash
# Function: 根据输入的程序的名字过滤出所对应的PID，并显示出详细信息，如果有几个PID，则全部显示
read -p "请输入要查询的进程名：" NAME
N=`ps -aux | grep $NAME | grep -v grep | wc -l`    ##统计进程总数
if [ $N -le 0 ];then
  echo "该进程名没有运行！"
fi
i=1
while [ $N -gt 0 ]
do
  echo "进程PID: `ps -aux | grep $NAME | grep -v grep | awk 'NR=='$i'{print $0}'| awk '{print $2}'`"
  echo "进程命令：`ps -aux | grep $NAME | grep -v grep | awk 'NR=='$i'{print $0}'| awk '{print $11}'`"
  echo "进程所属用户: `ps -aux | grep $NAME | grep -v grep | awk 'NR=='$i'{print $0}'| awk '{print $1}'`"
  echo "CPU占用率：`ps -aux | grep $NAME | grep -v grep | awk 'NR=='$i'{print $0}'| awk '{print $3}'`%"
  echo "内存占用率：`ps -aux | grep $NAME | grep -v grep | awk 'NR=='$i'{print $0}'| awk '{print $4}'`%"
  echo "进程开始运行的时刻：`ps -aux | grep $NAME | grep -v grep | awk 'NR=='$i'{print $0}'| awk '{print $9}'`"
  echo "进程运行的时间：`  ps -aux | grep $NAME | grep -v grep | awk 'NR=='$i'{print $0}'| awk '{print $11}'`"
  echo "进程状态：`ps -aux | grep $NAME | grep -v grep | awk 'NR=='$i'{print $0}'| awk '{print $8}'`"
  echo "进程虚拟内存：`ps -aux | grep $NAME | grep -v grep | awk 'NR=='$i'{print $0}'| awk '{print $5}'`"
  echo "进程共享内存：`ps -aux | grep $NAME | grep -v grep | awk 'NR=='$i'{print $0}'| awk '{print $6}'`"
  echo "***************************************************************"
  let N-- i++
done
```

清除系统缓存、空出更多内存

```bash
free -m && sync && echo 1 > /proc/sys/vm/drop_caches && echo 2 > /proc/sys/vm/drop_caches && echo 3 > /proc/sys/vm/drop_caches && echo 4 > /proc/sys/vm/drop_caches && sync && free -m
```

kill -9 杀不死进程，查看是否有僵尸进程,如果有,kill掉该进程的父进程

```bash
ps -A -ostat,ppid,pid,cmd | grep -e '^[Zz]'
```

根据关键词找到在哪个文件内容中

```bash
grep '9f82164b10d044bd-b1cdeb575153de91' /path/to/fe/log/fe.audit.log
```

查看/mnt/error_log目录下最近2分钟产生的文件

```bash
find /mnt/error_log -type f -mmin -2
```

