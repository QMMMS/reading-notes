# 环境检查与基础工具

## 代理

```python
import os

# os.environ['HTTP_PROXY'] = 'http://127.0.0.1:10809'
# os.environ['HTTPS_PROXY'] = 'http://127.0.0.1:10809'

# 检查代理是否有用
def check_proxy():
    import urllib.request
    url = "https://www.google.com"
    filename = "google.html"
    urllib.request.urlretrieve(url, filename)

check_proxy()  # 如果可以正常保存 google 网页，代理运行正常
```

## LangSmith

LangSmith 是一个追踪 langgraph 项目运行的在线网站。前往 https://smith.langchain.com/ 开一个账号并创建项目，在langgraph 项目前，需要如下设置以开启追踪

```python
os.environ['LANGSMITH_TRACING'] = 'true'
os.environ['LANGSMITH_ENDPOINT'] = 'https://api.smith.langchain.com'
os.environ['LANGSMITH_API_KEY'] = 'xxxxxx'
os.environ['LANGSMITH_PROJECT'] = 'xxxxxx'
```

随后，可以使用如下代码测试

```python
from langchain_openai import ChatOpenAI

llm = ChatOpenAI(
    model="gpt-4o-mini",
    api_key="xxxxxxxxxxxxxxxxx",
    base_url="xxxxxxxxxxxxx"
)
print(llm.invoke("just say 'hi'"))
```
