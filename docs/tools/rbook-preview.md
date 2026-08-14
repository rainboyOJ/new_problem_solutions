# rbook preview

位置：

```text
bin/rbook.js
```

作用：自动预览最近编辑的题解，并在相关文件保存后刷新所有已连接的浏览器。它只服务当前活动题目，避免 `npm start` 前置的全量题库扫描。

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

启动时扫描 `problems/**/index.md`，选择修改时间最新且能够完整渲染的文章。修改时间相同时按规范化路径排序，保证结果稳定。如果最新文件正在保存或内容无效，会继续尝试下一个有效文件；没有任何有效文章时命令会退出并报告错误。

终端会输出当前题目、来源文件、监听方式和本机/LAN 地址：

```text
Previewing luogu P1001
Source: luogu/P1001/index.md
Watching all problem index files and the active problem directory (500ms stability).
Access URLs:
- http://127.0.0.1:3000/problems/luogu/P1001/
```

## 自动刷新与切换

预览服务监听所有题目的 `index.md`，以及当前活动题目目录内的全部文件。文件事件会等待 500ms 稳定并合并处理。

- 保存当前 `index.md`、`problem.md`、`@include-code` 引用的代码或其他活动目录文件，会完整刷新所有已连接的浏览器。
- 保存另一题的有效 `index.md`，会把活动题目切换到最近修改的有效文章，并让所有浏览器跳转到新的规范 URL。
- 非活动题目目录中的普通文件变化会被忽略。
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

页面 URL 必须对应当前活动题目。旧题目页面 URL 会跳转到当前题目，旧题目 API 和静态资源不会继续提供。预览模式不提供首页题目列表、题单页或完整关系图。
