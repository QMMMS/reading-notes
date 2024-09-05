# 认识系统服务

## 服务启动关闭

------

- `systemctl start 服务`：立即启动服务 
- `systemctl stop 服务`：立即关闭服务 
- `systemctl restart 服务`：立即重启服务 
- `systemctl reload 服务`：重新加载配置文件

## 开机自启动

------

- `systemctl enable 服务`：下次开机自启动
- `systemctl disable 服务`：取消开机自启动

## 查询服务状态

------

- `systemctl status 服务`：列出服务状态

**例子：**

```
[root@qmmms ~]# systemctl status firewalld
● firewalld.service - firewalld - dynamic firewall daemon
   Loaded: loaded (/usr/lib/systemd/system/firewalld.service; disabled; vendor preset: enabled)
   Active: inactive (dead)
     Docs: man:firewalld(1)
```

## 查看所有服务

------

- `systemctl list-units`：查看已经启动的服务
- `systemctl list-units --all`：查看所有服务

**例子：**

```
[root@qmmms ~]# systemctl list-units --all | head
  UNIT                                                                           LOAD      ACTIVE   SUB       DESCRIPTION
  proc-sys-fs-binfmt_misc.automount                                              loaded    active   waiting   Arbitrary Executable File Formats File System Automount Point
  dev-disk-by\x2did-virtio\x2d116c6b92\x2da9bc\x2d4086\x2db.device               loaded    active   plugged   /dev/disk/by-id/virtio-116c6b92-a9bc-4086-b
  dev-disk-by\x2did-virtio\x2d116c6b92\x2da9bc\x2d4086\x2db\x2dpart1.device      loaded    active   plugged   /dev/disk/by-id/virtio-116c6b92-a9bc-4086-b-part1
  dev-disk-by\x2dpath-pci\x2d0000:02:01.0.device                                 loaded    active   plugged   /dev/disk/by-path/pci-0000:02:01.0
  dev-disk-by\x2dpath-pci\x2d0000:02:01.0\x2dpart1.device                        loaded    active   plugged   /dev/disk/by-path/pci-0000:02:01.0-part1
  dev-disk-by\x2dpath-virtio\x2dpci\x2d0000:02:01.0.device                       loaded    active   plugged   /dev/disk/by-path/virtio-pci-0000:02:01.0
  dev-disk-by\x2dpath-virtio\x2dpci\x2d0000:02:01.0\x2dpart1.device              loaded    active   plugged   /dev/disk/by-path/virtio-pci-0000:02:01.0-part1
  dev-disk-by\x2duuid-6c533615\x2dcacd\x2d47a7\x2d844e\x2d10013da6d35b.device    loaded    active   plugged   /dev/disk/by-uuid/6c533615-cacd-47a7-844e-10013da6d35b
  dev-ttyS0.device  
```

> 注：这些内容是最基础的使用，更多使用方法看书