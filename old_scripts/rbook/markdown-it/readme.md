# markdown-r

配置[markdown-it](https://github.com/markdown-it/markdown-it)给我自己使用

## Demo

[Demo online](https://rainboylvx.github.io/markdown-r/)

## 支持的语法

- [markdown-it-kbd](https://github.com/jGleitz/markdown-it-kbd) 键盘,keystrokes 样式显示

Renders `[[x]]` as `<kbd>x</kbd>`. ([`<kbd>`](http://www.w3schools.com/tags/tag_kbd.asp) is the tag for keystrokes).

- [markdown-it-footnote](https://github.com/markdown-it/markdown-it-footnote) ,脚注

```
Normal footnote:
Here is a footnote reference,[^1] and another.[^longnote]

[^1]: Here is the footnote.

[^longnote]: Here's one with multiple blocks.

    Subsequent paragraphs are indented to show that they
belong to the previous footnote.

Inline footnote:
Here is an inline note.^[Inlines notes are easier to write, since
you don't have to pick an identifier and move down to type the
note.]
```

## 如何使用

```javascript
var md = require('markdown-r')
md.render('# hello world')
```


**需要的html引入的 js 与css**

```
<link rel="stylesheet" href="github-markdown.css">
<link rel="stylesheet" href="/prism-theme/prism-tomorrow.css">
<link rel="stylesheet" href="/markdown-r.css">
<link rel="stylesheet" href="">
```

```
<script src="https://cdn.bootcss.com/jquery/3.4.1/jquery.min.js"></script>
<script src="https://unpkg.com/viz.js@2.1.2/viz.js"></script>
<script src="https://unpkg.com/viz.js@2.1.2/full.render.js"></script>
<script src="/vizRender.js"></script>
<script type="text/x-mathjax-config">
    MathJax.Hub.Config({
      TeX: { extensions: ["autoload-all.js"] },
      extensions: ["tex2jax.js"],
      jax: ["input/TeX", "output/HTML-CSS"],
      tex2jax: {
        //-<!--$表示行内元素，$$表示块状元素 -->
        inlineMath: [ ['$','$'], ["\\\(","\\)"] ],
        displayMath: [ ['$$','$$'], ["\\\[","\\]"] ],
        processEscapes: true
      },
      "HTML-CSS": {
        availableFonts: ["STIX","TeX"] ,
        showMathMenu:false
      },
      CommonHTML: { scale: 100 }
    });
</script>
<script async src="https://cdn.bootcss.com/mathjax/2.7.6/MathJax.js"></script>
```

## 测试

```
npm run test
```

## 使用的插件

| 插件                        | 作用          |
|-----------------------------|---------------|
| prismjs                     | 代码高亮      |
| twemoji                     | emoji         |
| markdown-it-abbr            | abbr          |
| markdown-it-container       | 块            |
| markdown-it-emoji           | emoji         |
| markdown-it-imsize          | img大小       |
| markdown-it-inline-comments | 注释          |
| markdown-it-ins-del         | 下划线/删除线 |
| markdown-it-kbd             | key样式       |
| markdown-it-mark            | mark          |
| markdown-it-mathjax         | tex公式       |
| markdown-it-multimd-table   | table         |
| markdown-it-sub             | 上标          |
| markdown-it-sup             | 下标          |
| markdown-it-task-checkbox   | checkbox      |
| markdown-it-toc-and-anchor  | toc           |


## viz-gallery

需要的`js`资源: https://github.com/rbookr/web-components

 - full.render.js
 - viz.js
 - vue.js
 - viz-gallery.js
    - cdn: https://cdn.jsdelivr.net/gh/rbookr/web-components/dist/viz-gallery/viz-gallery.min.js

语法如下

```
<<<< viz-gallery(title="demo",engine="dot",height="400")

​``` 这是log1
graph G{
  a--b;
}
​```

​``` neato 这是 log2
graph G{
  a--b;
}
​```
<<<<

```


## emoji

- [twemoji cheat sheet](http://rainboy.coding.me/twemoji_cheat_sheet/)
- [emoji cheat sheet](http://rainboy.coding.me/twemoji_cheat_sheet/)

## image size

```
![test](image.png =100x200)
```


## 其他

```
++insert++ 下划线
~~insert~~ 删除线
```

## pangu


```javascript
var md = require("./index.js")
md.options.pangu = true
console.log(md.render("與PM戰鬥的人，應當小心自己不要成為PM"))
```

参考自:
- [中英文排版空格问题解决方案 | 静觅](https://cuiqingcai.com/6533.html)
- [vinta/pangu.js: Paranoid text spacing in JavaScript](https://github.com/vinta/pangu.js)
- [中文文案排版指北（简体中文版） — 码志](https://mazhuang.org/wiki/chinese-copywriting-guidelines/)

## 图片轮播


```
::: lb
![](1.png)
![](2.png)
![](3.png)
:::
```

### container 的使用

目前有`blackboard`,`class`,`warning`,`error`,`info`

使用:

```
::: warning
::: 

::: error
::: 

::: info
::: 


::: blackboard
:::

```

```
::: class line
:::

::: line
:::

```

引入`markdown-r.js markdown-r.css`

### code tab


```

\`\`\`js [g1:JavaScript]
console.log("hello");
\`\`\`

\`\`\`py [g1:Python3]
print("hello")
\`\`\`

```


### mermaid的支持


这里有一个插件 https://github.com/tylingsoft/markdown-it-mermaid
但是太老了

查了一下,好像不能直接使用

根据这个issue: https://github.com/mermaid-js/mermaid/issues/3650


这个时候有两种方法实现

1. 根据官网的例子: 把代码嵌入到 `pre.mermaid`里，然后使用cdnjs 进行初始化渲染:`mermaid.initialize({ startOnLoad: true });`
2. 使用`makefile + mermaidjs-cli,渲染所有的本地的文件成为svg,然后通过图片引入`



### iframe


https://github.com/rjriel/markdown-it-iframe


```
Below will render an iframe

/i/https://www.youtube.com/embed/qkcx0kf6jME
```

不好的地址,网址必须要以https开头

