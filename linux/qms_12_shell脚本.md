# shell脚本

更加细节的知识请参考`bin`文件夹下的一系列脚本

这个markdown文档展示最一般的HelloWorld脚本，从编写到执行或调试的流程

## 脚本新建编写

------

在家目录新建一个`bin`文件夹，在里面新建脚本（因为`~/bin`下的脚本和程序可以直接执行）

```
[qms@qmmms ~]$ mkdir bin
[qms@qmmms ~]$ cd bin
[qms@qmmms bin]$ vim HelloWorld.sh
```

脚本内容如下

```shell
#!/bin/bash
echo "Hello World!"
exit 0
```

然后给予可执行权限

```
[qms@qmmms bin]$ chmod 700 HelloWorld.sh 
[qms@qmmms bin]$ ll
total 4
-rwx------ 1 qms qms 39 Sep 25 12:30 HelloWorld.sh
```

## 脚本执行

------

```
[qms@qmmms bin]$ ./HelloWorld.sh 
Hello World!
[qms@qmmms bin]$ sh HelloWorld.sh 
Hello World!
[qms@qmmms bin]$ source HelloWorld.sh 
Hello World!
```

- `./HelloWorld.sh`和`sh HelloWorld.sh`命令会新开一个子bash，父bash和子bash的变量等内容互不影响
- `source HelloWorld.sh`命令直接在父bash里面执行

## 脚本跟踪和调试

------

**格式：**

```shell
sh [参数] 脚本
```

**参数：**

- `-n`：不执行脚本，只检查语言错误
- `-x`：实时显示正在执行的脚本行

**例子：**

```
[qms@qmmms bin]$ sh -x HelloWorld.sh 
+ echo 'Hello World!'
Hello World!
+ exit 0
```

