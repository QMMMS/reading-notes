# Playwright

Playwright 为现代网络应用程序提供可靠的端到端测试

## 开始

```python
import re
from playwright.sync_api import Page, expect, sync_playwright

# https://playwright.dev/python/docs/writing-tests

def test_has_title(page: Page):
    page.goto("https://playwright.dev/")

    # Expect a title "to contain" a substring.
    expect(page).to_have_title(re.compile("Playwright"))
    # 如果成功会继续往下走，如果失败会抛出异常

def test_get_started_link(page: Page):
    page.goto("https://playwright.dev/")

    # Click the get started link.
    page.get_by_role("link", name="Get started").click()

    # Expects page to have a heading with the name of Installation.
    expect(page.get_by_role("heading", name="Installation")).to_be_visible()
```

运行方式有两种，包括使用 pytest ，或者通过 mian 函数调用

关于 pytest

- 在命令行中运行 pytest 时会自动调用，或者使用 vscode 插件进行测试，文件名必须以 test_ 开头或者 _test 结尾
- 要在有头模式下运行测试，请使用 --headed 标志，其他 CLI 参数参考文档
- 要记录轨迹，`pytest --tracing on`，生成的轨迹文件在 test-results 目录下，要查看轨迹，`playwright show-trace trace.zip`

关于通过 mian 函数调用

```python
if __name__ == "__main__":
    with sync_playwright() as p:
        browser = p.chromium.launch(headless=False)  # 设置 False 显示浏览器
        context = browser.new_context()
        page = context.new_page()

        # 调用测试函数
        test_has_title(page)
        page.wait_for_timeout(2000)  # 等待2秒
        test_get_started_link(page)
        page.wait_for_timeout(2000)  # 等待2秒

        expect(page).to_have_title(re.compile("Error")) # 故意让它失败，抛出异常

        browser.close()
```

## 操纵浏览器

实例1：截图

```python
from playwright.sync_api import sync_playwright

with sync_playwright() as p:
    browser = p.webkit.launch(headless=False)  
    # 默认是 True 不显示浏览器，设置 False 显示浏览器
    page = browser.new_page()
    page.goto("https://playwright.nodejs.cn/")
    page.screenshot(path="example.png")
    browser.close()
```

实例2：百度搜索

```python
from playwright.sync_api import Playwright, sync_playwright
# 导入 定时器
# from time import sleep


# 创建浏览器
def run (playwright: Playwright) -> None:

  # 创建浏览器
  browser = playwright.chromium.launch(headless=False)

  # 使用 selenium 如果要打开多个网页，需要创建多个浏览器，但是 playwright 中只需要创建多个上下文即可
  # 例如：content1 = browser.new_context()、content2 = browser.new_context() 分别去访问网页做处理
  content = browser.new_context()

  # 每个 content 就是一个会话窗口，可以创建自己的页面，也就是浏览器上的 tab 栏，在每个会话窗口中，可以创建多个页面，也就是多个 tab 栏
  # 例如：page1 = content.new_page()、page2 = content.new_page() 封面去访问页面
  page = content.new_page()

  # 页面打开指定网址
  page.goto('https://www.baidu.com')

  # 找到百度输入框（ locator 会自动识别传入的选择器是 css xpath .... 不需要像 selenium 指定 By.XPATH/ID 这样的 ）
  # page.locator('//*[@id="chat-textarea"]').fill('周杰伦') # 也可以写成下面这样：
  page.fill('//*[@id="chat-textarea"]', '周杰伦')

  # 点击百度一下进行搜索
  # page.locator('//*[@id="chat-submit-button"]').click() # 也可以写成下面这样：
  page.click('//*[@id="chat-submit-button"]')

  # 延迟关闭（为啥需要延迟一下，这里是用于测试，因为代码执行完马上就回关闭，运行太快了，还以为崩溃了
  # 暂时没找到配置不需要进行自动关闭，但是肯定跟 selenium 一样有这个配置）
  page.wait_for_timeout(10000)

  # 使用完成关闭上下文（也就是会话窗口）
  content.close()

  # 关闭浏览器
  browser.close()

# 调用
with sync_playwright() as playwright:
  run(playwright)
```

## 自动生成测试代码

使用 `codegen` 命令运行测试生成器，后跟要为其生成测试的网站的 URL。URL 是可选的，如果省略，可以直接在浏览器窗口中添加

```shell
playwright codegen demo.playwright.dev/todomvc
```

在浏览器中运行 `codegen` 并执行操作。Playwright 会自动生成交互代码。代码生成器会分析渲染的页面，并推荐最佳定位器，优先考虑角色、文本和测试 ID 定位器。当多个元素与某个定位器匹配时，生成器会对其进行改进，使其能够唯一地标识目标元素，从而减少测试失败和不稳定的情况。

```python
import re
from playwright.sync_api import Playwright, sync_playwright, expect


def run(playwright: Playwright) -> None:
    browser = playwright.chromium.launch(headless=False)
    context = browser.new_context()
    page = context.new_page()
    page.goto("https://demo.playwright.dev/todomvc/#/")
    page.get_by_role("textbox", name="What needs to be done?").click()
    page.get_by_role("textbox", name="What needs to be done?").fill("say hello")
    page.get_by_role("textbox", name="What needs to be done?").press("Enter")
    expect(page.get_by_test_id("todo-title")).to_be_visible()
    page.get_by_role("checkbox", name="Toggle Todo").check()
    page.get_by_role("textbox", name="What needs to be done?").click()
    page.get_by_role("textbox", name="What needs to be done?").fill("smile")
    page.get_by_role("textbox", name="What needs to be done?").press("Enter")

    # ---------------------
    context.close()
    browser.close()


with sync_playwright() as playwright:
    run(playwright)
```

## 使用代理

> https://www.cnblogs.com/longronglang/p/18263434

```python
from playwright.sync_api import sync_playwright

proxy = {'server': 'http:/127.0.0.1:10808'}

def run():
    with sync_playwright() as p:
        browser = p.chromium.launch(headless=False, proxy=proxy)
        page = browser.new_page()
        page.goto('https://www.google.com')
        title = page.title()
        if "Google" in title:
            print("打开Google成功")
        else:
            print("打开Google失败")
        browser.close()

run()
```

## 异步写法

```python
from playwright.async_api import async_playwright
import asyncio

proxy = {'server': 'http:/127.0.0.1:10808'}

async def run():
    async with async_playwright() as p:
        browser = await p.chromium.launch(headless=False, proxy=proxy)
        page = await browser.new_page()
        await page.goto('https://www.google.com')
        title = await page.title()
        if "Google" in title:
            print("打开Google成功")
        else:
            print("打开Google失败")
        await browser.close()

asyncio.get_event_loop().run_until_complete(run())
```

1、同步的优点:

- 代码结构简单易懂,不需要学习`async/await`语法
- 适用于小规模或简单任务
- 调试和理解同步代码更简单

2、异步的优点:

- 能更高效地利用系统资源,避免阻塞等待IO
- 对于长时间操作如网络请求更高效
- 可以支持并发执行多个任务
- 对于大规模和复杂系统更有利

3、区别

- 对于小任务和学习用途,同步代码结构更简单。
- 对于需要长时间IO等待的任务(如网络请求),使用异步可以更高效。
- 对于需要支持高并发的系统(如网站),使用异步模型可以支持更多并发连接。
- 多线程同步会带来锁的问题,而异步避免了锁的使用。
- 异步的FUTURE模式也更易于扩展性好,支持动态增加回调函数。

4、总结

- 小任务用同步
- 长时间IO任务用异步
- 高并发系统用异步
- 以后的功能扩展考虑异步更灵活

一般来说对于现代化系统,异步编程模型将是主流趋势。但同步在某些场景也同样易用。选择时要根据具体需求来权衡。