# rbook preview

位置：

```text
bin/rbook.js
```

作用：预览一个题解，并在该题目目录内的文件保存后刷新所有已连接的浏览器。它只监听当前活动题目，避免 `npm start` 前置的全量题库扫描。

## 基本用法

在仓库根目录运行：

```bash
npm run preview
```

如果已经把仓库 `bin/` 加入 `PATH`，也可以运行：

```bash
rbook preview
rbook preview --port 3100
rbook preview --host 127.0.0.1
```

命令不再接收 OJ 和题号位置参数。默认监听 `0.0.0.0:3000`，可通过 `--host`、`--port/-p`、`HOST` 或 `PORT` 修改。服务不会自动打开浏览器。

## 自动选择

启动时扫描一次 `problems/**/index.md`，选择修改时间最新且能够完整渲染的文章。修改时间相同时按规范化路径排序，保证结果稳定。如果最新文件正在保存或内容无效，会继续尝试下一个有效文件；没有任何有效文章时命令会退出并报告错误。扫描完成后不会继续监听其他题目的 `index.md`。

终端会输出当前题目、来源文件、监听方式和本机/LAN 地址：

```text
Previewing luogu P1001
Source: luogu/P1001/index.md
Watching only problems/luogu/P1001 (500ms stability).
Access URLs:
- http://127.0.0.1:3000/problems/luogu/P1001/
```

## 手动切换题目

直接修改浏览器地址即可切换题目。下面三种地址都会激活 P1001，并规范化到带尾斜杠的页面 URL：

```text
/problems/luogu/P1001
/problems/luogu/P1001/
/problems/luogu/P1001/index.html
```

支持所有存在的 `problems/<oj>/<problem_id>/index.md`。Luogu 额外支持数字别名，例如 `/problems/luogu/1001` 会跳转到 `/problems/luogu/P1001/`。

切换是 preview 服务的全局行为：唯一监听目录随之切换，其他已连接的浏览器也会自动跳转到新题目。浏览器前进、后退或点击题目链接采用相同规则。不存在或无法渲染的题目返回 404，并保留当前有效页面与监听目录。

API、Md Raw 和静态资源请求不会激活题目。非活动题目的 API 或资源返回 404。

## 自动刷新

预览服务只递归监听当前活动题目目录。文件事件会等待 500ms 稳定并合并处理。

- 保存当前 `index.md`、`problem.md`、`@include-code` 引用的代码或其他活动目录文件，会完整刷新所有已连接的浏览器。
- 非活动题目目录完全不在 watcher 范围内，修改其中任何文件都不会刷新或切题。
- 无效、不完整、被删除或暂时不可读的文章不会替换页面。终端会显示简短错误，下一次有效保存会自动恢复。

同题刷新会保留文档滚动位置，但会关闭已打开的弹窗。切换题目会替换当前地址并从页面顶部开始。预览响应统一使用 `Cache-Control: no-store`，避免浏览器继续显示旧的页面、JSON 或静态资源。

## 渲染能力

预览服务复用主站的 `MarkdownRenderer` 和 `problem.pug`，支持：

- 展开 `@include-code(./main.cpp, cpp)`
- 当前题目目录下的相对图片和其他资源
- `problem.md` 原题面弹窗
- Md Raw 查看与复制展开后的 Markdown
- Mermaid、Graphviz/dot、KaTeX
- 浏览器端 Prism 代码高亮
- 代码复制按钮、字体工具栏和主题切换
- `/api/problems/:oj/:id` 单题 JSON

页面 URL 可以激活对应题目；API 和静态资源只能访问当前活动题目。预览模式不提供首页题目列表、题单页或完整关系图。
