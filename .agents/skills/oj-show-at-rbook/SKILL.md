---
name: oj-show-at-rbook
description: >-
  为一篇已写完的 OJ 题解维护 frontmatter 里指向 rbook 的两个字段：
  showAtRbook（本题要挂到哪些 rbook 文章下，值是文章 id 数组）和
  rbookLinks（本题要指向哪些 rbook 知识文章，值是 {id, label, reason} 对象数组）。
  从本地 rbook 书读取真实存在的文章 id，按题目内容筛候选，让用户挑选，再写回
  problems/<oj>/<problem_id>/index.md。用户要求「更新 showAtRbook」「填充 rbookLinks」
  「给这道题补 rbook 知识链接」「把题解挂到 rbook 某篇文章下」「题解关联 rbook 文章」，
  或在题目交付后需要决定这两个字段时使用。
  本 skill 只写这两个字段，不写 pre / common / recommend，不改题解正文，不生成图。
---

# 更新 showAtRbook / rbookLinks

把一道题解和 rbook 书连起来。两个字段都只存**文章 id**，不存 URL，渲染时由
`lib/rbook-articles.js` 从 rbook catalog 实时解析成标题和链接。

## 两个字段的分工

| 字段 | 语义 | 值格式 | 读者视角 |
| --- | --- | --- | --- |
| `showAtRbook` | 这道**题解**是 rbook 某篇文章的例题/练习，挂到文章下 | 字符串数组，元素是文章 id | 在 rbook 文章页看到「相关题解」 |
| `rbookLinks` | 这道**题**要先掌握 rbook 里哪些知识，正向指出去 | 对象数组 `{ id \| url, label?, reason }` | 在题目详情页看到「相关知识」 |

判断标准：文章讲的知识**在本题之前**、值得读者先去看 → `rbookLinks`；文章拿这道题当
例子或练习、读者应该从文章过来 → `showAtRbook`。同一篇文章通常只落在一边，两侧都硬挂
会让读者绕圈。

`pre` / `common` / `recommend` 是题与题之间的关系，由
[`oj-problem-relation-writer`](../oj-problem-relation-writer/SKILL.md) 维护，不混写。

## 两个 rbook 站：id 只属于 rbook2

仓库旁边有两个 rbook 站，它们**寻址方式不同**，这决定了 `rbookLinks` 该写 `id` 还是 `url`：

| | `newRbook_ejs`（`rainboyOJ/rbook`） | `rbook_nunjucks`（`rainboyOJ/rbook_nunjucks`） |
| --- | --- | --- |
| 线上 | `https://rbook.roj.ac.cn` | `https://rbook2.roj.ac.cn` |
| 形态 | 纯静态，`dist/` 里没有任何 `api*` | Node 服务，有 `/api/health`、`/api/catalog` |
| 文章身份 | md 里**没有** `id:`，id 由 `idFromPath()` 从目录名推导 | frontmatter 手写 `id:`（线上 447 篇 / 329 个模板） |
| 本地路径 | `~/mycode/newRbook_ejs`（`RBOOK2_CODE_PATH` **不**指向它） | `~/mycode/rbook_nunjucks/book` |

结论：

- **`id` 只能指 rbook2（nunjucks）。** `lib/rbook-articles.js` 用 `RBOOK_API_BASE_URL`
  （默认 `https://rbook2.roj.ac.cn`）拉 `/api/catalog` 解析 id，只有这本有 catalog；
  `list_rbook_articles.py` 读的 `RBOOK2_CODE_PATH` 也是同一本，所以校验与渲染同源。
- **链 rbook.roj.ac.cn 只能用 `url`。** 那本没有 API、也没有手写 id，路径才是它的身份。
- 两边有 29 个同名 id，其中 `base`、`mst`、`minimal-string`、`other` 四个指向**不同**文章。
  今天不出问题（ejs 不参与解析），但不要假设 id 跨站唯一。

`url` 形态写法：`https://rbook.roj.ac.cn/<catalog.yaml 里的 path>/`（尾斜杠可省略，实测
`/data_structure/heap/` 与 `/data_structure/heap/index.html` 都是 200）。路径从
`~/mycode/newRbook_ejs/book/catalog.yaml` 查，不要猜。

## 触发方式

**手动触发优先。** 用户点名要求更新 `showAtRbook` 或 `rbookLinks` 时，直接按本 skill 执行。

**交付后询问。** 在 [`oj-problem-workflow`](../oj-problem-workflow/SKILL.md) 走完一道题
的交付、进入「完成与报告」阶段时，问用户一句是否要顺便补这两个字段。用户不要求就跳过，
不自动写入。

不在这两个时机之外主动改这两个字段。

## 数据来源：只读本地书，不联网

文章 id 全部从本地 rbook 书取，不依赖线上服务。

### 1. 定位 book 目录

按顺序取第一个存在的：

1. 环境变量 `RBOOK2_CODE_PATH` 的值（它指向书目录根，即 `book.yaml` 所在目录）。
2. `~/mycode/rbook_nunjucks/book`。

两者都没有 `book.yaml` 时停下，报告「未找到 book.yaml」并询问用户书的位置。不要猜路径，
不要凭记忆编造 id。

### 2. 用脚本取可用文章清单

```bash
S=.agents/skills/oj-show-at-rbook/scripts/list_rbook_articles.py

python3 $S --grep 线段树 二分        # 按关键词筛候选
python3 $S --verify sgt-update-one,binary-search   # 校验具体 id
python3 $S                          # 全部可用文章（约 444 篇）
python3 $S --json                   # 机器可读
```

**写文件前，两个字段里每个要写入的 id 都必须过一遍 `--verify`。** 这一步是硬要求：id 写错
时线上会静默丢掉链接，页面上什么都不显示，很难发现。

### 3. 为什么不能按 book.yaml 过滤，也不能裸扫 pages

两个坑，都实测过：

- **`book.yaml` 不是收录范围。** 它只是导航目录，只有 176 个条目，而书里实际可解析的文章有
  445 篇。按 `book.yaml` 过滤会漏掉一大半可用文章。
- **裸扫 `book/pages/**/*.md` 会把草稿写进去。** `pages` 下有 470 个带 `id` 的 markdown，
  其中 25 个是草稿、TODO、草稿归档，它们不在任何目录里，线上也不生成页面。

脚本采用的判定规则（从 470 篇反向标定，与线上 445 篇对齐到 444 篇）：

> 候选 = `book/pages` 下所有带 frontmatter `id` 的 markdown，**排除**「所在目录名含『草稿』」
> 或「文件名（不含扩展名）含 `草稿` / `todo` / `draft`」的文件。

已知的一处保守偏差：`graph-algorithm-book-note-archive`（路径
`Books/todo_图论与算法_程龚.md`）线上仍在目录里，但脚本按 `todo` 前缀把它排除了。这个偏差
方向是安全的（少给候选，不会写出无效 id），遇到时用 `--all` 查看即可。

### 4. id 在文件里的位置

每篇文章在 `book/pages/**/index.md` 的 frontmatter 里：

```yaml
---
id: "sgt-update-one"
title: "线段树：单点修改与区间查询"
---
```

`id` 可能在 `index.md`，也可能在 `草稿/` 之外的任意 md 文件里（例如 `Books/xxx.md`、
`data_structure/segment_tree/other.md`），所以脚本按 `rglob('*.md')` 扫，不要只找
`index.md`。

## 交互：先搜再选

文章有几百篇，不能整表铺给用户。

1. **从当前题提炼关键词。** 读当前题 `index.md` 的 `tags`、`title`、`description`，
   加上正文讲到的核心算法名。线段树题会得到 `线段树`、`二分`、`区间最值`、`sgt`、
   `binary-search`。
2. **用 `--grep` 多跑几个关键词**，把候选收窄到 10 条以内。优先给真正讲同一算法或同一
   数据结构原理的文章，不要为了凑数把沾边的都列上。
3. **用 `ask_user` 多选让用户挑。** 每个选项写 `id` 与 `title`，并给出挂载理由（为什么这道
   题属于这篇文章 / 为什么读者该先读这篇）。同时允许用户自由补充不在候选里的 id。
   一次请求里同时问清要不要写另一个字段，不要拆成两轮。
4. **校验用户手填的 id**，不在可用清单里就明确告知「这个 id 不在可用范围内（可能是草稿或
   拼错）」并让用户改选。不要直接写入。
5. **保留已有值。** 当前字段非空时，把已有条目一并展示，让用户决定保留、增补还是替换。
   不要静默覆盖。

用户明确说「你自己判断」时才跳过第 3 步，但仍要把最终选择列出来让用户确认。

判断关联的分寸：优先选**讲同一数据结构 / 同一算法原理**的文章。只是用到同一个词（比如都
出现「线段树」但一篇讲扫描线、一篇讲树上二分）不算强关联。倒过来的情形也不强求——比如一道
维护下标线段树区间最大值的题，和一篇讲值域线段树查第一个小值位置的文章，骨架同源但语义
相反，可以作为「对照」挂上，但不要写成前置。

## 写入

只改 `problems/<oj>/<problem_id>/index.md` 的 frontmatter，字段顺序按
[`oj-problem-format-spec`](../oj-problem-format-spec/references/frontmatter.md)：
`categories` → `showAtRbook` → `rbookLinks` → `pre`。

```yaml
categories: []
showAtRbook: ["sgt-update-one"]
rbookLinks:
  - id: "sgt-value-first-less"              # rbook2 的手写 id
    label: "线段树二分：找第一个小值位置"   # 可选，缺省时用文章标题
    reason: "本题主解的线段树上跳跃就是这篇的模板"
  - url: "https://rbook.roj.ac.cn/data_structure/heap/"   # ejs 站只能写 url
    label: "堆"
    reason: "本题用堆维护候选集，先看这篇的堆实现"
pre: []
```

规则：

- `showAtRbook` 保持字符串数组，元素是文章 id，顺序即展示顺序。它只有 rbook2 一种形态。
- `rbookLinks` 元素必须**二选一**：写 `id`（rbook2 手写 id）或写 `url`（rbook.roj.ac.cn
  的文章地址）。不要两个都写，不要留空。
- `reason` 必填，一句话说清「为什么读这篇才能做本题」，不写「相关」「可参考」这类空话。
- `label` 可选：`id` 形态缺省时用 catalog 里的文章标题；`url` 形态**没有 catalog 可查**，
  必须写 `label`。
- **选哪种：先想 `id`。** 只要那篇在 rbook2 上有手写 id，就写 `id`——它能自动同步标题、
  坏链不显示、换域名不用改全库。只有 rbook2 上确实没有对应文章、或者要指到
  rbook.roj.ac.cn 的老站文章时才写 `url`。
- 锚点：`id` 形态不带锚点（目录解析不认）；`url` 形态可以带 `#小节`，这也是需要深链时的
  唯一手段。
- 不要写 Markdown 链接（`[文字](url)`），字段里只有裸 URL。
- `updated` 刷成当前本地时间 `YYYY-MM-DD HH:MM`，保留原 `date`。
- 其余字段、正文、代码引用一概不动。
- 用户要清空时写 `showAtRbook: []` / `rbookLinks: []`。

## 校验

三件事按顺序做完，任何一步不过都要修：

1. **逐个核对 id**（两个字段的 id 合并去重后一起校验）：

```bash
python3 .agents/skills/oj-show-at-rbook/scripts/list_rbook_articles.py --verify <id1>,<id2>,...
```

退出码非 0 说明有无效 id，不能交付。`--verify` 只管 `id` 形态；`url` 形态的条目要自己
确认能打开（`curl -s -o /dev/null -w '%{http_code}' <url>` 得 200，跟随便重定向）。

2. **确认 YAML 能解析、`updated` 已刷新**，格式为 `YYYY-MM-DD HH:MM`：

```bash
python3 -c "import yaml,sys;d=yaml.safe_load(open(sys.argv[1]).read().split('---')[1]);print(d.get('showAtRbook'));print([x.get('id') for x in (d.get('rbookLinks') or [])])" problems/<oj>/<problem_id>/index.md
```

3. **跑目录检查**：

```bash
python3 scripts/problem-analysis-tools/check_problem.py problems/<oj>/<problem_id>
```

批量任务把全库 `npm run check:content` 留给主 agent 统一跑；单题任务可以自己跑一次。

## 当前渲染状态（写之前知道）

`showAtRbook` 已经接到页面：`lib/rbook-articles.js` 拉 `/api/catalog` 解析 id → 标题 + url，
`views/problem.pug` 渲染。

`rbookLinks` 目前**只在攒数据**：前端还没有读取和渲染它，`lib/problem.js` 也不校验它的形状
（`id` 写错、`url` 404、`id`/`url` 都缺，都不会报错）。写进去页面上暂时看不到。要用起来需要
另做一轮工程改动（`lib/problem.js` 加归一化、`url` 形态直接透传、`id` 形态复用
`RbookArticleService` 解析、`views/problem.pug` 渲染、补测试并跑 `npm run verify:push`）。
本 skill 不负责那部分。

## 报告

简短说明：

- 改了哪个题目目录、写了哪个字段。
- 写入了哪些条目：`id` 形态给文章标题，`url` 形态给 `label` 与 200 校验结果，各自写理由。
- 保留 / 新增 / 移除了哪些原有条目。
- `--verify`、`url` 探活与 `check_problem.py` 的结果。
- 还有哪些候选没写入，以及原因（含「本该用 id 但 rbook2 上没有这篇文章」这类降级到 url 的
  判断）。

## 不要做的事

- 不要联网拉 catalog 或依赖线上服务来取 id。
- 不要按 `book.yaml` 过滤候选（会漏 60% 文章），也不要裸扫 `pages` 不过滤草稿（会写进
  无效 id）。
- 不要写 Markdown 链接（`[文字](url)`），字段里只有裸 URL。
- 不要给 `id` 形态加锚点，也不要把 rbook2 的文章写成 `url`（白丢标题同步和坏链检测）。
- 不要拿 `idFromPath()` 推导出的 ejs id 当 `id` 写进 `rbookLinks`——那本书没有 API，
  解析不到；该写 `url`。
- 不要编造文章 id 或标题。
- 不要改 `pre` / `common` / `recommend`；需要时提示转 `oj-problem-relation-writer`。
- 不要改题解正文、代码或图示。
- 用户没要求时不要自动写入这两个字段。
