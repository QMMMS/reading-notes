# 软件管理

## 软件安装方式介绍

|  发行商代表   | 软件管理机制 | 使用命令 | 在线升级命令 |
| :-----------: | :----------: | :------: | :----------: |
| Fedora/CentOS |     RPM      |   rpm    |     yum      |
| Debian/Ubuntu |     DPKG     |   dpkg   |   apt-get    |

因为正在使用 CentOS，所以这里介绍 RPM

## RPM查询

**常用命令如下：**

- `rpm -q 软件`：仅查询软件是否安装
- `rpm -qa`：列出所有已安装软件
- `rpm -qi 软件`：列出软件详细信息
- `rpm -ql 软件`：列出软件所有文件目录所在文件名
- `rpm -qf 文件`：找出该文件属于哪个软件

**例子：**

```
[user1@qmmms ~]$ rpm -q gcc
gcc-4.8.5-44.el7.x86_64
```

## RPM安装

命令`rpm`是本地安装，首先要准备好`.rpm`文件

```shell
rpm -ivh 包
```

- `-i`：表示安装
- `-v`：显示信息安装信息
- `-h`：显示安装进度条

注：更加详细的安装过程（挂载光盘、查看依赖）请看书

## RPM卸载

```shell
rpm -e 软件
```

注意，如果有其他软件依赖于这个要卸载的软件，卸载不会成功

## 获取校验码

要获取 MD5，SHA-1，SHA-256 等算法得到的校验码，**格式为：**

```shell
md5sum 文件
```

```shell
sha1sum 文件
```

```shell
sha256sum 文件
```

**例子：**

```
[user1@qmmms ~]$ md5sum /etc/passwd
9e35fc8333741cfb858784863621f9b1  /etc/passwd
```

## YUM 查询

常用功能如下：

- `yum search 关键字`：查找相关软件
- `yum list`：列出所有yum管理的软件，列出信息的格式为`软件名 版本 软件源`
- `yum info 软件`：列出软件详细信息
- `yum provides 文件`：找出该文件属于哪个软件

**例子：**

```
[user1@qmmms ~]$ yum list | head
Loaded plugins: fastestmirror
Loading mirror speeds from cached hostfile
Installed Packages
GeoIP.x86_64                             1.5.0-14.el7                  @base    
NetworkManager.x86_64                    1:1.18.8-2.el7_9              @updates 
NetworkManager-libnm.x86_64              1:1.18.8-2.el7_9              @updates 
NetworkManager-team.x86_64               1:1.18.8-2.el7_9              @updates 
NetworkManager-tui.x86_64                1:1.18.8-2.el7_9              @updates 
acl.x86_64                               2.2.51-15.el7                 @anaconda
aic94xx-firmware.noarch                  30-6.el7                      @anaconda
```

```
[user1@qmmms ~]$ yum provides passwd
Loaded plugins: fastestmirror
Loading mirror speeds from cached hostfile
passwd-0.79-6.el7.x86_64 : An utility for setting or changing passwords using PAM
Repo        : base
passwd-0.79-6.el7.x86_64 : An utility for setting or changing passwords using PAM
Repo        : @anaconda
```

## YUM 安装和升级

命令`yum`是在线安装和升级，直接给软件名称就行

```shell
yum install 软件
```

```shell
yum update 软件
```

## YUM卸载

------

```shell
yum remove 软件
```

## YUM软件群组

YUM软件群组功能可以安装一系列软件，使用语法与上面相似

```shell
yum grouplist
yum groupinfo 软件群组
yum groupinstall 软件群组
yum groupremove 软件群组
```

**例子：**

```
[user1@qmmms ~]$ yum grouplist | head
Loaded plugins: fastestmirror
There is no installed groups file.
Maybe run: yum groups mark convert (see man yum)
Loading mirror speeds from cached hostfile
Available Environment Groups:
   Minimal Install
   Compute Node
   Infrastructure Server
   File and Print Server
   Cinnamon Desktop
   MATE Desktop
   Basic Web Server
```

## 安装软件与开启服务的一般流程

------

1. 安装：`yum install 软件`
2. 开启服务：`systemctl start 软件`
3. 开机启动：`systemctl enable 软件`
4. 设置防火墙：`firewall-cmd --permanent  --add-service="服务"`
5. 测试

## 实例：开启WWW网站服务器

首先查询相关软件是否安装，然后安装它们

```
[root@qmmms ~]# rpm -q httpd php mariadb-server php-mysql
package httpd is not installed
package php is not installed
package mariadb-server is not installed
package php-mysql is not installed
[root@qmmms ~]# yum install httpd php mariadb-server php-mysql
```

有很多输出的信息，这里截取最后几行，可以看到已经安装好了很多相关软件

```
Installed:
  httpd.x86_64 0:2.4.6-97.el7.centos.5       mariadb-server.x86_64 1:5.5.68-1.el7       php.x86_64 0:5.4.16-48.el7 
  php-mysql.x86_64 0:5.4.16-48.el7          
Dependency Installed:
  apr.x86_64 0:1.4.8-7.el7                                   apr-util.x86_64 0:1.5.2-6.el7                         
  httpd-tools.x86_64 0:2.4.6-97.el7.centos.5                 libaio.x86_64 0:0.3.109-13.el7                         
  libzip.x86_64 0:0.10.1-8.el7                               mailcap.noarch 0:2.1.41-2.el7                         
  mariadb.x86_64 1:5.5.68-1.el7                              perl-Compress-Raw-Bzip2.x86_64 0:2.061-3.el7           
  perl-Compress-Raw-Zlib.x86_64 1:2.061-4.el7                perl-DBD-MySQL.x86_64 0:4.023-6.el7                   
  perl-DBI.x86_64 0:1.627-4.el7                              perl-Data-Dumper.x86_64 0:2.145-3.el7                 
  perl-IO-Compress.noarch 0:2.061-2.el7                      perl-Net-Daemon.noarch 0:0.48-5.el7                   
  perl-PlRPC.noarch 0:0.2020-14.el7                          php-cli.x86_64 0:5.4.16-48.el7                         
  php-common.x86_64 0:5.4.16-48.el7                          php-pdo.x86_64 0:5.4.16-48.el7                         
Complete!
```

开启服务

```
[root@qmmms ~]# systemctl daemon-reload
[root@qmmms ~]# systemctl start httpd
[root@qmmms ~]# systemctl enable httpd
Created symlink from /etc/systemd/system/multi-user.target.wants/httpd.service to /usr/lib/systemd/system/httpd.service.
[root@qmmms ~]# systemctl enable httpd
```

设置防火墙

```
[root@qmmms ~]# firewall-cmd --add-service="http"
success
[root@qmmms ~]# firewall-cmd --permanent  --add-service="http"
success
[root@qmmms ~]# firewall-cmd --reload
success
[root@qmmms ~]# firewall-cmd --list-all
public (active)
  target: default
  icmp-block-inversion: no
  interfaces: eth0
  sources: 
  services: dhcpv6-client http ssh
  ports: 80/tcp
  protocols: 
  masquerade: no
  forward-ports: 
  source-ports: 
  icmp-blocks: 
  rich rules: 
```

之后在你的电脑的浏览器上输入远程服务器的 ip 地址，就可以看到网页

如果在服务器上开启了图形模式并打开浏览器，输入 localhost 就可以看到网页

![网页服务器](https://linux.vbird.org/linux_basic/centos7/0520softwaremanager/testing.jpg)

如果想要展示自己的网页，在`/var/www/html/`中编辑`index.html`文件