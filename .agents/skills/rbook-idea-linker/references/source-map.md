# 两本 rbook 的来源与判据

两条来源的“什么算一篇文章”“id 从哪来”“公开地址怎么拼”都不同，混用会写出打不开的链接。
下面每条都是在本机实测过的，不是从旧文档抄的。

## rbook1：`https://rbook.roj.ac.cn`

本地源码 `~/mycode/newRbook_ejs`（或环境变量 `RBOOK1_CODE_PATH`）。

### 纯静态站，没有 REST API

`/api/site`、`/api/pages`、`/api/catalog`、`/api/codes`、`/api/health` 在 rbook1 上全部返回 404。
不要照搬 `rbook-http` 的接口去查 rbook1，也不要把 rbook2 的 `scripts/rbook.py` 指到 rbook1 域名。

构建期会额外产出 `dist/catalog.json`（`id` / `title` / `url` 清单，见
`src/publishing/pipeline/catalog-manifest.ts`），但**未部署线上**（`https://rbook.roj.ac.cn/catalog.json`
仍 404）。本地 `dist/catalog.json` 存在时可以用 `--manifest` 读它（id/url 由构建保证可点），
但它可能落后于源码；日常以 `catalog.yaml` 为准，脚本会在两边对不上时打一行提示。

### 收录范围 = `book/catalog.yaml` 的叶子

实测（2026-11，书在持续编辑，数字会变，规则不变）：`catalog.yaml` 有 **141** 个叶子条目，
`dist/` 下 **170** 个 HTML，其中 141 个与叶子逐一对应，其余是 `teach_plan.html`、`canvas/**`、
`assets/autoindex/**` 等附属页——**叶子一个不少**，这是每次重构后都应重跑的校验：

```bash
node .agents/skills/rbook-idea-linker/scripts/list-rbook1-articles.mjs --json | \
  node -e "let s='';process.stdin.on('data',d=>s+=d).on('end',()=>{const fs=require('fs');const a=JSON.parse(s);console.log('dist 缺失:',a.filter(x=>x.url&&!fs.existsSync('/home/rainboy/mycode/newRbook_ejs/dist'+x.url+(x.url.endsWith('/')?'index.html':''))).length)})"
```

`book/` 下共有 **272** 个 `.md`，也就是有一百多 md 不在目录里。抽查确认它们没有对应的
`dist` HTML，线上 404，例如：

- `book/algorithm/binary_search/index.md` → `/algorithm/binary_search/index.html` **404**
- `book/algorithm/discrete/start.md`、`book/algorithm/dsu_on_tree/index.md` 同样未发布

所以：**只看 `catalog.yaml` 叶子，不要裸扫 `book/**/*.md`**。裸扫会把未发布草稿当成可用文章，
写出的链接线上打不开。这与 rbook2 侧“`book.yaml` 不等于收录范围”的坑方向相反，别把两边规则套错。

### id 与标题的来源

- 每个文章目录里可能有 `config.json` / `config.jsonc` / `config.yaml` / `config.yml`（`book/` 下
  共 75 个 `config.json`），字段是 `id`、`title`、`file`、`code_template`、`pre`、`next` 等。
- **不要以为 rbook1 没有 id。** md 的 frontmatter 确实没写 `id`，但 `config.*` 里有，例如
  `book/base/binary_jump/config.yaml` 是 `id: binary_jump`、`book/data_structure/segment_tree/sgt_merge/`
  是 `id: sgt_merge`。`showAtRbook-and-rbookLinks` 的表里写“md 里没有 `id:`、id 由 `idFromPath()` 从目录名
  推导”，那是只说了一半：`metadata-normalizer.ts` 的顺序是**先用 config 的 `id`，缺了才回落
  `idFromPath()`**。两者会不一样：`sgt_first_lt/` 目录名推出来是 `sgt_first_lt`，实际 id 是
  `sgt_lower_bound`。核 id 一律读 config，不要自己拼目录名。
- `file` 缺省为 `index.md`；目录叶子没有 config 时（例如 `book/recursion/practice.md`）才纯按路径
  推导：文件名是 `index` 就用目录名，否则用文件名。
- 标题优先取 config 的 `title`，缺失时用 `catalog.yaml` 的 `title`（后者一定有，侧边栏显示的就是它）。
- `config.json` 是 **JSONC**：带 `//` 注释和尾逗号，`JSON.parse` 会直接报错（实测 75 个里有 11 个）。
  解析要容错，脚本里已有 `stripJsonc`。

### 公开地址

站内路径的规则：

| 叶子形态 | 地址 | 实测 |
| --- | --- | --- |
| 目录型（绝大多数） | `/<catalog.yaml 里的 path>/` | `/base/presum/` **200**；`/base/presum/index.html` 也是 200；`/base/presum`（无尾斜杠）**301** |
| 文件型（如 `practice.md`、`graph/preface.md`） | `/<path>.html` | `/recursion/practice.html` **200** |

例：

| id | 源 | 公开地址 |
| --- | --- | --- |
| `presum` | `book/base/presum/index.md` | `https://rbook.roj.ac.cn/base/presum/` |
| `binary_jump` | `book/base/binary_jump/index.md` | `https://rbook.roj.ac.cn/base/binary_jump/` |
| `jump_lca` | `book/tree/jump-lca/index.md` | `https://rbook.roj.ac.cn/tree/jump-lca/` |
| `practice` | `book/recursion/practice.md` | `https://rbook.roj.ac.cn/recursion/practice.html` |

正文里的链接写完整域名；`rbookLinks` 只能写 `url`（rbook1 没有可解析的 catalog），同样用这个
形态，带锚点时才加 `#小节`。不把 config 的 id 当路径。

### 状态字段

部分文章 frontmatter 有 `status: TODO`（实测 23 处，其中一部分在目录里，如
`book/appendix/python/index.md`、`book/graph/tarjan/cut/index.md`）。它们**已经发布**、链接可用，
但内容未定稿：可以引用，但要说明这一点，或优先选讲得更完整的文章。

## rbook2：`https://rbook2.roj.ac.cn`

本地源码 `~/mycode/rbook_nunjucks`。

- 正文在 `book/pages/**`，导航在 `book/book.yaml`。篇数随书增长，**以脚本输出为准**：
  实测 `472` 个带 `id` 的 md，可用 `446` 篇、排除 `26` 篇草稿。
- **`book.yaml` 不是收录范围**：它只是导航目录（176 个条目），按它过滤会漏掉一大半。
- **裸扫 `book/pages` 会把草稿写进去**：带 `id` 的 md 里有一批是草稿、TODO、草稿归档，
  线上不生成页面。
- 判定规则：候选 = `book/pages` 下所有带 frontmatter `id` 的 markdown，
  排除「所在目录名含『草稿』」或「文件名含 `草稿` / `todo` / `draft`」的文件。
- 现成工具：`.agents/skills/showAtRbook-and-rbookLinks/scripts/list_rbook_articles.py`（支持 `--grep`、
  `--verify`、`--json`、`--all`）。用它，不要另写一份扫描逻辑。
- 需要线上 id、详情或 URL 时按 `rbook-http` 走 `/api/pages`、`/api/codes`，客户端是
  `/home/rainboy/mycode/rbook_nunjucks/scripts/rbook.py`，显式指定
  `--baseurl https://rbook2.roj.ac.cn`。该客户端的 `find` 只搜目录元数据，不能替代正文检索。
- 代码模板在 `book/code.yaml` + `book/code/<path>`，字段是 `id`、`path`、`description`、
  `language`、`tags`。rbook1 **没有** `code.yaml`，别在 rbook1 找模板清单。

## 目录归属

- `/home/rainboy/mycode/rbook_new_problem_solutions` 是题解库，不是任何一本书的源码。
- 两本书存在同名 id，不能互相替代。引用哪本，域名和路径就必须属于哪本。

## 路径失效时

执行前核实目录存在。环境变量优先：

- `RBOOK1_CODE_PATH`（指向 `book/` 或仓库根，脚本两种都认）
- `RBOOK2_CODE_PATH`（指向 rbook2 的 `book/`）

路径或站点对应关系变了就报告并停下，不默默换源、不凭记忆编 id 或 URL。
