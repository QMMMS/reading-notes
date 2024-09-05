# 进程管理

## 前后台管理

------

### 后台执行命令

**格式：**

```shell
命令 &
```

**例子：**

```
[root@qmmms ~]# tar -zpcf /tmp/etc.tar.gz /etc &
[1] 2847
[root@qmmms ~]# tar: Removing leading `/' from member names
```

一段时间后，再输入随便什么命令，后台任务完成会有提示

```
[1]+  Done                    tar -zpcf /tmp/etc.tar.gz /etc
```

**注意：**

- 后台执行的任务无法使用[Ctrl+c]终止，可以用一些命令调用（后面说）

- 后台执行的任务不能等待用户输入

- 后台任务的输出会出现在屏幕上，可以使用重定向将这些输出导入文件，例如：

    ```shell
    tar -zpcvf /tmp/etc.tar.gz /etc > /tmp/log.txt 2>&1 &
    ```

### 将当前任务放入后台

快捷键 [ctrl]+z 可以使当前任务暂停并放入后台

**例子：**在进行 vim 编辑文件的时候按 [ctrl]+z

```
[user1@qmmms ~]$ vim doc

[1]+  Stopped                 vim doc
```

### 查看后台任务

**格式：**

```shell
jobs [参数]
```

**参数：**

- `-l`：同时列出 PID
- `-r`：只列出正在后台**运行**的任务
- `-s`：只列出正在后台**暂停**的任务

### 将后台任务调到前台

**格式：**

```shell
fg [%任务号码]
```

**例子**：将后台中的`vim doc`调到前台

```
[user1@qmmms ~]$ jobs -l
[1]-  2965 Stopped                 vim doc
[2]+  3009 Stopped                 find / -print
[user1@qmmms ~]$ fg %1
```

**注意：**

- `[2]+`的加号代表这是最近暂停的任务，如果`fg`命令不带参数，则默认调用最近暂停的任务
- `[1]-`的减号代表这是最近第二个暂停的任务

### 将后台任务在后台继续运行

```shell
bg %任务号码
```

### 结束后台任务

**格式：**

```shell
kill [参数] %任务号码
```

**参数：**

- `-1`：重新读取参数配置
- `-9`：立即强制删除任务
- `-15`：正常结束任务

## 脱机任务

------

在脱机或注销系统后，后台的任务会结束运行

如果要让任务在脱机继续运行，使用命令

- `nohup 命令`：前台执行
- `nohup 命令 &`：后台执行

## 查看进程

------

- `ps -l`：查看自己bash进程
- `ps aux`：查看系统全部进程
- `pstree`：查看进程树
- `pstree -up`：查看进程树，同时列出 PID (`-p`) 和所属账号 (`-u`)
- `top`：动态查看所有进程
- `top -p [PID]`：动态查看某个PID指示的进程

> `top`是一个动态的程序，进入`top`的一些常见操作如：
>
> - `q`：退出
> - `?`：查看帮助
> - `P`：以CPU使用排序显示
> - `M`：以内存使用排序显示

```
[user1@qmmms ~]$ ps -l
F S   UID   PID  PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
0 S  1000  2671  2670  0  80   0 - 28920 do_wai pts/0    00:00:00 bash
0 R  1000  5582  2671  0  80   0 - 38332 -      pts/0    00:00:00 ps
```

```
[user1@qmmms ~]$ ps aux | head
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root         1  0.0  0.2 125372  3844 ?        Ss   11:36   0:01 /usr/lib/systemd/systemd --switched-root --system --deserialize 22
root         2  0.0  0.0      0     0 ?        S    11:36   0:00 [kthreadd]
root         4  0.0  0.0      0     0 ?        S<   11:36   0:00 [kworker/0:0H]
root         5  0.0  0.0      0     0 ?        S    11:36   0:00 [kworker/u4:0]
root         6  0.0  0.0      0     0 ?        S    11:36   0:00 [ksoftirqd/0]
root         7  0.0  0.0      0     0 ?        S    11:36   0:00 [migration/0]
root         8  0.0  0.0      0     0 ?        S    11:36   0:00 [rcu_bh]
root         9  0.0  0.0      0     0 ?        S    11:36   0:00 [rcu_sched]
root        10  0.0  0.0      0     0 ?        S<   11:36   0:00 [lru-add-drain]
```

```
[user1@qmmms ~]$ pstree
systemd─┬─NetworkManager─┬─dhclient
        │                └─2*[{NetworkManager}]
        ├─2*[agetty]
        ├─atd
        ├─auditd───{auditd}
        ├─chronyd
        ├─crond
        ├─dbus-daemon
        ├─hostguard───20*[{hostguard}]
        ├─hostwatch───2*[{hostwatch}]
        ├─irqbalance
        ├─master─┬─pickup
        │        └─qmgr
        ├─polkitd───6*[{polkitd}]
        ├─rsyslogd───2*[{rsyslogd}]
        ├─sshd─┬─sshd───sshd─┬─bash───pstree
        │      │             └─sftp-server
        │      └─6*[sshd───sshd]
        ├─systemd-journal
        ├─systemd-logind
        ├─systemd-udevd
        ├─tuned───4*[{tuned}]
        ├─uniagent───9*[{uniagent}]
        └─wrapper─┬─java───17*[{java}]
                  └─{wrapper}
```

## 进程管理

------

**格式：**

```shell
kill [参数] PID
```

**参数：**

- `-1`：重新读取参数配置
- `-9`：立即强制删除任务
- `-15`：正常结束任务