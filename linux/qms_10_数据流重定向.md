# 数据流重定向

通俗来讲，本来数据要传到A处，但让它传到B处

-   标准输入，代码为0，使用`<`
-   标准输出，代码为1，使用`>`，`>>`
-   标准错误输出，代码为2，使用`2>`，`2>>`

## 标准输出

------

-   `>`：以**覆盖**方式将屏幕输出传到指定文件或设备上
-   `>>`：以**累加**方式将屏幕输出传到指定文件或设备上

**例子：**

```
[user1@qmmms ~]$ ll > ll_info
[user1@qmmms ~]$ cat ll_info 
总用量 684
drwxrwxrwT 2 user1 basic_users   4096 9月   2 17:24 dir_test
-rw------- 1 user1 basic_users    348 9月  12 15:05 doc
-rw-r--r-- 1 user1 basic_users      0 9月  17 10:39 ll_info
-rw-r--r-- 1 user1 basic_users    752 9月  12 16:13 lucas.cpp
-rwxr-xr-x 1 user1 basic_users   8360 9月   2 13:36 sayhi
-rw-r--r-- 1 user1 basic_users 670293 9月  12 10:46 services
drwxrwxrwt 2 root  root          4096 9月   4 23:05 tmp
```

## 标准错误输出

------

-   `2>`：以**覆盖**方式将屏幕错误输出传到指定文件或设备上
-   `2>>`：以**累加**方式将屏幕错误输出传到指定文件或设备上

**例子：**

```
[user1@qmmms ~]$ qmmms 2> wrong_info
[user1@qmmms ~]$ cat wrong_info 
-bash: qmmms: 未找到命令
```

## 组合用法

------

### 写入不同文件

```
[user1@qmmms ~]$ find /home -name .bashrc > list_right 2> list_error
[user1@qmmms ~]$ cat list_right 
/home/user1/.bashrc
[user1@qmmms ~]$ cat list_error 
find: ‘/home/qms’: 权限不够
```

### 输出转化

-   `1>&2`：将标准输出转到标准错误输出
-   `2>&1`：将标准错误输出转到标准输出

**例子：**

```
[user1@qmmms ~]$ find /home -name .bashrc > list 2>&1
[user1@qmmms ~]$ cat list
find: ‘/home/qms’: 权限不够
/home/user1/.bashrc
```

### 黑洞设备

如果对于某些输出，不想在屏幕上看到，也不想保存到文件，那么可以重定向到`/dev/null`黑洞设备

**例子：**

```
[user1@qmmms ~]$ find /home -name .bashrc > list 2> /dev/null         
[user1@qmmms ~]$ cat /dev/null
[user1@qmmms ~]$ 
```

## 标准输入

------

-   `<`：本来要键盘输入的数据，转而由文件提供

**例子：在程序中使用数据文件代替键盘输入**

写一个简单加法C++文件（simple_add.cpp）

```cpp
#include<iostream>
using namespace std;

int main(){
	int n = 0;
	int num = 0;
	while(cin >> num) n += num;
	cout << n << endl;
	return 0;
}
```

编辑一个数据文件（data.in）

```
1 2 3 4 5 6 7 8 9 10
```

编译后执行

```
[user1@qmmms ~]$ g++ -o ./simple_add simple_add.cpp 
[user1@qmmms ~]$ ./simple_add < data.in 
55
```

## 双向重定向

------

`tee`命令可以让其他命令的屏幕输出保留，同时留存一份到文件

**格式：**

```shell
其他命令 | tee [参数] 文件
```

**参数：**

-   没有参数，直接覆盖文件
-   `-a`：以追加的方式加入数据到文件

**例子：**

```
[user1@qmmms ~]$ date | tee date_list
2022年 09月 17日 星期六 18:39:24 CST
[user1@qmmms ~]$ cat date_list 
2022年 09月 17日 星期六 18:39:24 CST
```

