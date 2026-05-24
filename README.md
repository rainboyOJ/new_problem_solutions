# rbook 题目库项目

这是一个基于 Fastify 的题目库网站，题目来源于 `problems/` 目录中的 Markdown 文件。项目同时提供：

- 网页浏览与检索（Pug + Bootstrap）
- RESTful API（供程序和 AI 调用）
- MCP 网关（`./mcp`，用于 AI 工具化调用）

## 1. 功能概览

- Markdown 题目渲染（Front Matter + 正文）
- 题目列表分页、OJ/标签筛选、搜索
- 题目详情页渲染
- API 接口：
  - `GET /api/problems`
  - `GET /api/problems/:oj/:id`
  - `GET /api/tags`
  - `GET /api/oj`
  - `GET /api`（API 文档页）
- 双链解析：`[[oj/problem_id]]`

## 2. 环境要求

- Node.js 18+
- npm

## 3. 启动网站服务

在项目根目录执行：

```bash
npm install
npm start
```

默认访问地址：

- 网站首页：`http://127.0.0.1:3000/`
- API 文档：`http://127.0.0.1:3000/api`

## 4. 使用 MCP（给 AI 调用）

MCP 服务位于 `./mcp`，它会调用上面的主站 API。

### 4.1 安装与启动

```bash
cd mcp
npm install
TARGET_API_BASE_URL=http://127.0.0.1:3000 npm start
```

默认监听：`http://127.0.0.1:3333`

### 4.2 MCP 提供的核心工具

- `search_problems`
- `get_problem_detail`

详细说明见：`mcp/README.md`

## 5. 项目结构

```text
.
├── app.js                 # Fastify 应用构建入口
├── bin/www                # 网站启动脚本
├── lib/                   # 核心模块（题目管理、markdown 渲染等）
├── routes/                # 页面路由与 API 路由
├── views/                 # Pug 模板
├── public/                # 静态资源
├── problems/              # 题目 Markdown 数据（本地数据源）
├── mcp/                   # MCP 网关服务
└── docs/                  # 设计与计划文档
```

## 6. 常用命令

### 根项目

```bash
npm test
npm start
```

源码阅读路径见：`docs/source-guide.md`

### MCP 子项目

```bash
cd mcp
npm test
npm start
npm run start:stdio
```

## 7. 开发说明

- 题目数据来自 `problems/`，启动时会扫描并用于检索。
- 如需扩展 AI 能力，优先在 `mcp/src/tools/` 下新增工具。
- API 变更后，请同步更新：
  - `views/api.pug`
  - `mcp/README.md`
