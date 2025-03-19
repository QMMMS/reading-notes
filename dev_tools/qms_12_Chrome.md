# Chrome

允许复制：

```js
javascript:"use strict";
!function() {
    var t = function(t) {
        t.stopPropagation(),
        t.stopImmediatePropagation && t.stopImmediatePropagation()
    };
    ["copy", "cut", "contextmenu", "selectstart", "mousedown", "mouseup", "keydown", "keypress", "keyup"].forEach(function(e) {
        document.documentElement.addEventListener(e, t, {
            capture:!0
        })
    }),
    alert("success")
}();
```

自由修改网页

```
document.designMode="on"
```

其他：

- 截图：Ctrl+shift+P，full
- 修改 CSS 与 盒模型
- 查看事件监听器，并跳转到函数
- 本地编辑网页，同步 chrome 与本地文件（来源-工作区）
- 更多-渲染-显示图层
- 更多-网络状况-修改用户代理
- 更多-屏蔽网络请求，编写表达式屏蔽广告等资源
