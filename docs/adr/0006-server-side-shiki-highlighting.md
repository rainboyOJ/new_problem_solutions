# 0006 代码高亮改用服务端 Shiki

## 状态

已采纳（2026-11-11）

## 背景

代码高亮一直是 Prism：浏览器端加载 Prism core + autoloader，按 `language-*` 类名按需拉语法包，主题是 `prism-tomorrow`。

三个问题：

1. **配色跟主题割裂**。Tomorrow 是深色专用配色，代码块外壳又写死 `#2d2d2d`；站点有浅色/深色切换，浅色模式下满屏深色砖块。
2. **语法精度不够**。Prism 的 C++/Python 语法是正则堆出来的，模板尖括号、raw string、Python f-string 这类边界容易分错色。
3. **运行时开销**。每个页面都要跑一遍 `highlight(document)`，语言包按需异步加载，首屏会看到先无色后变色的闪烁。

## 决策

**用 Shiki 在服务端预渲染，浏览器不再做语法分析。**

- `lib/highlight.js` 封装高亮：`createHighlighterCoreSync` + 纯 JS 正则引擎，模块加载阶段一次性读入 25 个语法包和 2 个主题，之后所有渲染路径同步可用，`MarkdownRenderer.toHTML()` 不需要变成 async。
- **双主题输出**：`themes: { light: 'github-light', dark: 'github-dark' }`，浅色写进 `style` 的 `color`，深色写进 `--shiki-dark` 变量，由 CSS 在 `[data-bs-theme="dark"]` 下用 `!important` 覆盖（内联样式优先级高于样式表，必须加）。
- **代码块外壳也跟主题走**：`--rb-code-bg` / `--rb-code-border` / `--rb-code-header-bg` 等一组变量，浅色深色各一套，和 token 颜色对齐。
- **运行时内容走接口**：Md Raw 弹窗、随机数据生成器这类打开后才知道内容的代码，`POST /api/highlight` 拿服务端算好的 HTML。浏览器端 `code-highlight.js` 从「语法分析」退化成「贴 HTML」，不再需要打包 Shiki（完整语法包约 1MB，gzip 135KB）。
- 服务端渲染的代码块带 `data-rbook-highlight="server"`，前端看到就跳过，不发多余请求。

## 为什么用 JS 引擎而不是 oniguruma wasm

Shiki 默认走 oniguruma wasm，需要额外搬运 `onig.wasm` 并在启动时异步初始化。纯 JS 引擎的代价是慢一点，但：

- 实测对全部 1647 个真实代码块，两种引擎输出**逐字节一致**；
- 单块渲染 2–7ms，整库预热一遍约 11s，命中 LRU 缓存后为 0；
- 部署链（`scripts/build-native-release.sh` 只做 `npm ci --omit=dev`）不需要任何额外步骤。

## 语言覆盖

按 `problems/**` 与 `problem-sets/**` 的实际 fence 标签统计选型，只装用得到的 25 个语法：`cpp` `python` `haskell` `javascript` `typescript` `json` `bash` `markdown` `html` `css` `yaml` `java` `c` `rust` `go` `csharp` `kotlin` `lua` `ruby` `php` `pascal` `scala` `perl` `julia` `ocaml`。

`text` / `plain` / `none` / `inputN` / `outputN` 这类只描述数据的标签统一按纯文本输出，不上色也不发请求。未知标签同样退回转义后的纯文本，代码始终可读。

## 影响

- `prismjs` 依赖与 `/vendor/prism/` 静态挂载移除，`lib/prism-assets.js` 删除，`views/includes/prism-client.pug` 改名 `code-highlight-client.pug`。
- `/api/problems/:oj/:id` 的 `html_content` 现在**带** token 标记（以前明确不带，由浏览器补）。这是对外契约变化：外部若依赖「服务端不输出 token」，需要相应调整。
- 新增 `POST /api/highlight`，`views/api.pug` 已登记。
