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

