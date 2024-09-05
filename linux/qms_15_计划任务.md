# 计划任务

Linux 可以自动执行某些工作，包括一次性计划和周期计划

## 准备

------

atd 服务不是默认开启的，在某些版本 Linux 上需要手动开启（需要 root 身份）

```
[root@qmmms ~]# systemctl restart atd
[root@qmmms ~]# systemctl enable atd
[root@qmmms ~]# systemctl status atd
● atd.service - Job spooling tools
   Loaded: loaded (/usr/lib/systemd/system/atd.service; enabled; vendor preset: enabled)
   Active: active (running) since Sat 2022-10-01 15:28:38 CST; 1min 20s ago
 Main PID: 5681 (atd)
   CGroup: /system.slice/atd.service
           └─5681 /usr/sbin/atd -f

Oct 01 15:28:38 qmmms systemd[1]: Started Job spooling tools.
```

使用`at`命令需要权限，权限处理流程如下：

1. 如果`/etc/at.allow`文件存在，则只有这个文件里面的用户可以使用`at`命令
2. 如果`/etc/at.allow`文件**不存在**，并且`/etc/at.deny`文件**存在**，那么只有`/etc/at.deny`文件里面的用户不能使用`at`命令
3. 上面的文件都不存在，只有`root`可以使用`at`命令

使用`crontab`命令需要权限，流程与`at`命令相似，配置文件为`/etc/cron.allow`和`/etc/cron.deny`

## 一次性计划任务

------

### 创建一次性计划任务

**格式：**

```shell
at [参数] 时间
```

**参数：**

- `-m`：在计划完成后，给用户发一封邮件通知已完成

**时间格式：**

- `HH:MM`
- `HH:MM YYYY-MM-DD`
- 其他例子：`04pm July 30`，`now + 5 minutes`，`04pm + 3 days`

**注意：**

- 之后键入具体要执行的命令，这些命令会在预定的时间执行，注意按[Ctrl+d]作为结束

- 计划任务由系统自动执行，无论用户是否登录

- 计划任务命令使用独立的shell，环境与用户bash不同，建议命令和文件使用绝对路径

    > 提醒：查找命令绝对路径：`which 命令`

- 同上，`echo`命令的输出需要重定向到用户终端窗口

    > 提醒：查看用户终端窗口：`tty`

**例子：**

```
[user1@qmmms ~]$ at -m now + 1 minutes
at> echo "hellooooooooo" > /dev/pts/0
at> <EOT>
job 5 at Mon Oct  3 14:00:00 2022
```

### 管理一次性计划任务

- `atq`和`at -l`：列出一次性计划任务
- `at -c 任务号码`：列出任务的详细内容
- `atrm 任务号码`和`at -d 任务号码`：删除任务

## 周期计划任务

------

### 基本管理命令

**格式：**

```shell
crontab [参数]
```

**参数：**

- `-e`：进入编辑页面
- `-l`：查看内容
- `-r`：删除**所有**任务，若删除一项请`crontab -e`进入编辑

### 任务内容格式

`crontab -e`后会进入编辑页面，每一行代表一个任务，一行的格式为

```
分钟 小时 日期 月份 周 命令串
```

关于特殊字符意义：

| 字符 |   意义    |
| :--: | :-------: |
|  *   |   任意    |
|  ,   |    或     |
|  -   |   范围    |
|  /n  | 每n个单位 |

**例子：**

```
59 23 1 5 * 命令			#每年5-1 23:59执行命令
*/5 * * * *  命令			#每隔5分钟执行命令
30 16 * * 5 命令			#每周五16:30执行命令
```

## 系统计划任务

------

对于不是针对用户，而是针对系统的计划任务，直接编辑`/etc/crontab`文件

```
[root@qmmms ~]# cat /etc/crontab
SHELL=/bin/bash
PATH=/sbin:/bin:/usr/sbin:/usr/bin
MAILTO=root

# For details see man 4 crontabs

# Example of job definition:
# .---------------- minute (0 - 59)
# |  .------------- hour (0 - 23)
# |  |  .---------- day of month (1 - 31)
# |  |  |  .------- month (1 - 12) OR jan,feb,mar,apr ...
# |  |  |  |  .---- day of week (0 - 6) (Sunday=0 or 7) OR sun,mon,tue,wed,thu,fri,sat
# |  |  |  |  |
# *  *  *  *  * user-name  command to be executed
```

如注释所示，会多出一个user-name字段，代表以哪个身份执行
