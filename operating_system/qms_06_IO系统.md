# I/O系统

## I/O硬件

设备分类：

1. 块设备
2. 字符设备

I/O端口组成：

- 数据输入寄存器
- 数据输出寄存器
- 状态寄存器
- 控制寄存器

## 应用程序接口

- 字符设备接口
- 块设备接口
- 网络设备接口
- 时钟与定时器
- 向量I/O
- 阻塞/非阻塞/异步IO

> 非阻塞调用read()返回任何可用的数据。相比之下，异步调用read()会完整执行，但是将在未来某个时间完成。

## I/O控制方式

- 轮询
- 中断
- 直接内存访问（DMA）
- 通道。通道是**通过专用处理机来专门进行 I/O 传输，它有自己的 I/O 指令，执行期间不需要CPU干预**，而仅需在执行通道程序完成 I/O 后，产生 I/O 完成的中断，通知CPU。通道分为：字符多路通道、数组多路通道、数组选择通道。

> 管道：进程间通信方法。一个程序的输出可以作为另一个程序的输入。这样可以将多个程序串在一起，将简单的任务组合，处理更大更复杂的问题，unix中有这种技术。
>
> 管程：代表共享资源的数据结构，以及由对该共享数据结构实施操作的一组过程所组成的资源管理程序，共同构成了一个操作系统的资源管理模块，我们称之为管程。

## I/O子系统

主要目标：

- 提高设备利用率
- 为用户使用设备提供统一、抽象的接口

所需实现的主要功能包括：

- 设备统一命名
- I/O 调度
- 缓冲：提高主机和设备交换信息的速度，可以使用独立硬件缓冲器或者内存缓冲区。
- 缓存：磁盘高速缓存用于提高磁盘I/O速度，利用内存存储空间暂存磁盘中读出的磁盘块。因此缓存逻辑上属于磁盘，物理上属于内存。
- I/O 保护
- 错误处理
- SPOOLING（假脱机）与设备预留。

> 简述 SPOOLING 技术及其特点。
>
> 假脱机是对于独占设备，操作系统协调并发输出的一种方式（于是每一个进程都认为自己独占了设备），是保存数据输出的缓冲区。目的是提高独占设备利用率。
>
> 在 CPU 速度获得极大提升的情况下，以软件模拟代替脱机处理中的专用外围机，通过在磁盘上设立输入井和输出井，缓存 I/O 数据，将对低速设备的直接I/O 操作变为输入和输出进程对磁盘上输入井或输出井的操作，从而增加 CPU 与 I/O 设备异步并发工作能力，提升 I/O 效率。 其核心特点是：缓解了 CPU 与 I/O 速度不匹配的矛盾；允许将独占设备改造为共享设备；实现了虚拟设备的效果。