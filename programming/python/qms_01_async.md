# 并发编程

基础概念：

- 并发：一个 CPU 同时处理多个程序，但是在同一时间点只会处理其中一个。因为程序切换的速度非常快，1 秒钟内可以完全很多次程序切换，肉眼无法感知。

- 并行：多个 CPU 同时处理多个程序，同一时间点可以处理多个。

- 同步：执行 IO 操作时，必须等待执行完成才得到返回结果

- 异步：执行 IO 操作时，不必等待执行就能得到返回结果，异步适合 IO 密集任务，用在 CPU 密集型 发挥作用不大

- 多进程：利用多核 CPU 的优势，同时执行多个计算任务。每个进程有自己独立的内存管理，所以不同进程之间要进行数据通信比较麻烦

- 多线程：在一个 CPU 上创建多个子任务，当某一个子任务休息的时候其他任务接着执行。多线程的控制是由 python 自己控制的。 子线程之间的内存是共享的，并不需要额外的数据通信机制。但是线程存在数据同步问题，所以要有锁机制

- 协程：在一个线程内实现的，相当于流水线作业。由于线程切换的消耗比较大，所以对于并发编程，可以优先使用协程

### 异步/协程的基础使用

```python
import asyncio
import time

async def visit_url(url, response_time):
    """访问 url"""
    await asyncio.sleep(response_time)
    return f"访问{url}, 已得到返回结果"

start_time = time.perf_counter()
task = visit_url('https://www.baidu.com', 2)
asyncio.run(task)
print(f"消耗时间：{time.perf_counter() - start_time}")
```

- 在普通的函数前面加 async 关键字；
- await 表示在这个地方等待子函数执行完成，再往下执行。（在并发操作中，把程序控制权教给主程序，让他分配其他协程执行。） await 只能在带有 async 关键字的函数中运行。
- `asynico.run()` 运行程序
- 这个程序消耗时间 2s 左右

如果我们串行执行两个 async 任务，如下，这样编程的执行时间是 5 秒

```python
start_time = time.perf_counter()
task = visit_url('https://www.baidu.com', 2)
asyncio.run(task)
task2 = visit_url('https://www.baidu.com', 3)
asyncio.run(task2)
print(f"消耗时间：{time.perf_counter() - start_time}")
```

但是我们想要的效果是两个任务一起执行，因该消耗3秒才对！要想使用并发编程形式，需要把上面的代码改一下

```python
import asyncio
import time

async def visit_url(url, response_time):
    """访问 url"""
    await asyncio.sleep(response_time)
    return f"访问{url}, 已得到返回结果"

async def run_task():
    """收集子任务"""
    task = visit_url('https://www.baidu.com', 2)
    task_2 = visit_url('https://www.baidu.com', 3)
    results = await asyncio.gather(task, task_2)  # 这 2 个子任务之间进行调度
    return results


start_time = time.perf_counter()
results = asyncio.run(run_task())
print(results)
print(f"消耗时间：{time.perf_counter() - start_time}")
```

- `asyncio.gather` 会创建 2 个子任务，当出现 await 的时候，程序会在这 2 个子任务之间进行调度

- `asynico.run()` 运行的函数中，不能再调用`asynico.run()`

如果要明确 main 函数，可以这样编程

```python
import asyncio
import time

async def visit_url(url, response_time):
    """访问 url"""
    await asyncio.sleep(response_time)
    return f"访问{url}, 已得到返回结果"

async def main():
    start_time = time.perf_counter()
    tasks = [asyncio.create_task(visit_url('https://www.baidu.com', 2)) for _ in range(5)]
    results = await asyncio.gather(*tasks)
    for result in results:
        print(result)
    print(f"消耗时间：{time.perf_counter() - start_time}")

if __name__ == '__main__':
    asyncio.run(main())
```

总结一下：

- 异步模型是事件驱动模型的基础，是由于某种事件，才会有阻塞恢复行为，基于轮询或者说event_loop

- 它是一个单一线程，千万不能和多线程搞混了。只是在阻塞空闲的时候做额外的事

- 异步活动的执行模型可以只有一个单一的主控制流

- 能在单核心系统和多核心中运行，在并发执行的异步模型中，许多任务被穿插在同一时间线上，所有的任务都有一个控制流执行(单一线程)
