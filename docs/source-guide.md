# rbook 源码阅读指南

这份 guide 按运行链路阅读项目：先看网站如何启动，再看请求如何进入路由，最后看题目数据、Markdown 渲染和 MCP 网关。

## 1. 先建立项目地图

核心目录：

- `app.js`：Fastify 应用工厂，注册模板、静态文件、路由、404 和错误处理。
- `bin/www`：网站进程启动脚本，读取端口，调用 `app.listen()`，打印本机和局域网访问地址。
- `routes/`：HTTP 路由。`index.js` 负责网页，`api.js` 负责 JSON API 和 API 文档页。
- `lib/`：业务核心。题目索引、题目查询、Markdown 渲染、双链插件都在这里。
- `views/`：Pug 模板。
- `public/`：CSS 等静态资源。
- `problems/`：题目 Markdown 数据源，当前是指向外部题库目录的符号链接。
- `mcp/`：MCP LAN 网关，用 AI 工具接口封装网站 API。
- `old_scripts/`：历史抽离脚本和旧渲染实验，不是当前网站主链路。

推荐先读这些文件：

1. `package.json`
2. `bin/www`
3. `app.js`
4. `routes/index.js`
5. `routes/api.js`
6. `lib/problem.js`
7. `lib/markdown.js`
8. `mcp/src/server.js`

## 2. 网站启动链路

启动命令是：

```bash
npm start
```

实际执行 `node ./bin/www`。

`bin/www` 做三件事：

- 从 `PORT` 和 `HOST` 读取监听配置，默认 `3000` 和 `0.0.0.0`。
- 导入 `app.js` 默认导出的 Fastify 实例，并调用 `app.listen({ port, host })`。
- 启动成功后用 `lib/access-urls.js` 生成 `127.0.0.1` 和局域网 IP 访问地址。

`app.js` 的主函数是 `buildApp(options)`。它创建 Fastify 实例并注册：

- `@fastify/view`：用 Pug 渲染 `views/*.pug`。
- `@fastify/cookie`：解析 cookie。
- `@fastify/formbody`：解析表单 body。
- `@fastify/static`：把 `public/` 暴露成静态资源。
- `routes/index.js`：网页路由。
- `routes/api.js`：挂到 `/api` 前缀下。
- `setNotFoundHandler` 和 `setErrorHandler`：统一 404 和错误响应。

测试里会用 `buildApp({ logger: false })` 构建不监听端口的应用，再通过 `app.inject()` 直接发请求。

## 3. 网页请求链路

首页请求：

```text
GET /
```

进入 `routes/index.js`：

1. 读取 query：`q`、`oj`、`tag`、`page`。
2. 从 `problemManager.getAll()` 取全部题目。
3. 按搜索词、OJ、标签过滤。
4. 用本文件里的 `paginate()` 分页。
5. 调 `reply.view('index.pug', data)` 渲染首页。

题目详情页：

```text
GET /problems/:oj/:id
```

处理步骤：

1. 从路径参数拿 `oj` 和 `id`。
2. 用 `problemManager.find(oj, id)` 查题目元数据。
3. 找不到时调用 `reply.callNotFound()`。
4. 用 `problem.md_path` 定位 Markdown 文件。
5. 创建 `MarkdownRenderer`，调用 `toHTML()` 得到题面 HTML。
6. 渲染 `views/problem.pug`。

## 4. API 请求链路

API 路由在 `routes/api.js`，通过 `app.register(apiRoutes, { prefix: '/api' })` 挂载。

主要接口：

- `GET /api`：渲染 API 文档页。
- `GET /api/problems`：返回题目列表 JSON，支持 `page`、`limit`、`oj`、`tag`、`search`。
- `GET /api/problems/:oj/:id`：返回单题详情，包括 `md_content` 和 `html_content`。
- `GET /api/tags`：返回全部标签。
- `GET /api/oj`：返回全部 OJ。

注意 `GET /api/problems` 里的过滤是顺序覆盖式：

- 有 `oj` 时使用 `filterByOJ()`。
- 有 `tag` 时使用 `filterByTag()`。
- 有 `search` 时使用 `search()`。

这意味着多个条件同时存在时，后面的过滤不会基于前一个结果继续筛，而是重新从全量题库查询。这是当前代码行为，阅读和修改时要特别留意。

## 5. 题目数据链路

`lib/instance.js` 创建全局单例：

```js
const problemManager = new ProblemManager({ auto_load: true });
```

`ProblemManager` 在 `lib/problem.js`，核心状态：

- `this.problems`：题目元数据数组。
- `this.problemMap`：以 `${oj}/${problem_id}` 为 key 的快速索引。
- `this.config`：从 `book.yaml` 读取的配置，没有文件时返回空对象。

加载逻辑：

1. 默认读取根目录 `problems.json`。
2. 如果 `problems.json` 不存在，扫描 `problems/` 下所有非 `_` 开头的 Markdown 文件。
3. 每个 Markdown 读取 front matter，要求存在 `oj` 和 `problem_id`。
4. 生成 `url: /problems/:oj/:id`。
5. `buildIndex()` 填充 `problemMap`。

常用方法：

- `find(oj, problem_id)`：详情页和双链插件使用。
- `getAll()`：首页和 API 列表使用。
- `filterByTag(tag)`、`filterByOJ(oj)`、`search(keyword)`：筛选检索。
- `getAllTags()`、`getAllOJs()`：筛选下拉框和 API 使用。

## 6. Markdown 渲染链路

`lib/markdown.js` 里的 `MarkdownRenderer` 负责把题目 Markdown 转成 HTML。

构造时会创建 `MarkdownIt`：

- `html: true` 允许 Markdown 内 HTML。
- `linkify: true` 自动识别链接。
- `typographer: true` 开启排版替换。
- 注册 `createProblemLinkPlugin(problemManager)`。

读取文件时：

1. `readfile(md_path)` 读取 Markdown。
2. `processIncludeMd()` 递归处理形如 `@include_md("...")` 的包含语法。
3. `gray-matter` 分离 front matter 和正文。
4. `toHTML()` 调用 `markdown-it.render()`。
5. `toJSON()` 同时返回 front matter、Markdown 正文和 HTML。

双链插件在 `lib/markdown-plugins/problemLink.js`。它识别：

```text
[[poj/3061]]
```

如果能在 `ProblemManager` 里找到题目，就渲染成带 `problem-link` class 的 `<a>`；找不到则渲染为 warning 链接文字。

## 7. 模板层

模板都在 `views/`：

- `layout.pug`：公共 HTML 框架、导航、Bootstrap、静态 CSS。
- `index.pug`：题目列表、搜索框、OJ/标签筛选、分页。
- `problem.pug`：题目详情、面包屑、元数据、渲染后的 Markdown 内容。
- `api.pug`：API 文档页。
- `error.pug`：普通网页错误页。

Fastify 渲染入口是 `reply.view('xxx.pug', data)`。数据对象里的字段会直接成为模板变量。

## 8. MCP 网关链路

`mcp/` 是独立子项目，服务 AI 调用，不是网站渲染必须路径。

启动：

```bash
cd mcp
TARGET_API_BASE_URL=http://127.0.0.1:3000 npm start
```

主要文件：

- `mcp/src/config.js`：读取 `MCP_HOST`、`MCP_PORT`、`TARGET_API_BASE_URL`、超时和鉴权 token。
- `mcp/src/index.js`：HTTP/LAN 模式入口。
- `mcp/src/stdio.js`：stdio MCP 模式入口。
- `mcp/src/server.js`：MCP 协议服务、HTTP fallback 路由、SSE、错误格式化。
- `mcp/src/client/apiClient.js`：调用主站 API。
- `mcp/src/tools/searchProblems.js`：`search_problems` 工具。
- `mcp/src/tools/getProblemDetail.js`：`get_problem_detail` 工具。

典型 AI 查询链路：

```text
AI client
  -> mcp/src/server.js
  -> tools/searchProblems.js 或 tools/getProblemDetail.js
  -> client/apiClient.js
  -> 主站 /api/problems 或 /api/problems/:oj/:id
  -> routes/api.js
  -> lib/problem.js + lib/markdown.js
```

## 9. Express 到 Fastify 后的关键差异

这个项目现在的主站已经不使用 Express。

需要记住的写法变化：

- Express 的 `app.use(router)` 改为 Fastify 的 `app.register(plugin, { prefix })`。
- Express 的 `req.query`、`req.params` 在 Fastify 中是 `request.query`、`request.params`。
- Express 的 `res.render()` 改为 `reply.view()`。
- Express 的 `res.json()` 改为 `reply.send()`。
- Express 的 `next()` 404 改为 `reply.callNotFound()`。
- Express 中间件风格错误处理改为 `app.setErrorHandler()`。
- 静态文件由 `express.static()` 改为 `@fastify/static`。
- Pug 通过 `@fastify/view` 注册：`engine: { pug }`，模板文件使用 `views/*.pug`。

## 10. 修改代码时的阅读顺序

如果要改页面样式：

1. 看 `views/layout.pug`。
2. 看对应模板，例如 `views/index.pug` 或 `views/problem.pug`。
3. 看 `public/stylesheets/`。

如果要改题目检索：

1. 看 `routes/index.js` 的首页筛选。
2. 看 `routes/api.js` 的 API 筛选。
3. 看 `lib/problem.js` 的 `search()`、`filterByOJ()`、`filterByTag()`。
4. 再同步检查 MCP 的 `mcp/src/tools/searchProblems.js`。

如果要改 Markdown 能力：

1. 看 `lib/markdown.js`。
2. 看 `lib/markdown-plugins/`。
3. 用 `tests/markdown-problem-link.test.js` 补覆盖。

如果要改 MCP 工具：

1. 看 `mcp/src/tools/*.js` 的工具 schema 和返回结构。
2. 看 `mcp/src/client/apiClient.js` 的上游 HTTP 调用。
3. 看 `mcp/src/server.js` 的协议入口和错误封装。
4. 跑 `cd mcp && npm test`。

## 11. 验证命令

根项目：

```bash
npm test
npm start
```

MCP 子项目：

```bash
cd mcp
npm test
TARGET_API_BASE_URL=http://127.0.0.1:3000 npm start
```

快速人工验证：

```bash
curl -fsS http://127.0.0.1:3000/
curl -fsS 'http://127.0.0.1:3000/api/problems?limit=1'
curl -fsS http://127.0.0.1:3000/problems/poj/3061
```
