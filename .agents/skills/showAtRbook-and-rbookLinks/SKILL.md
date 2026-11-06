---
name: showAtRbook-and-rbookLinks
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

# 更新 showAtRbook 与 rbookLinks

把一道题解和 rbook 书连起来。两个字段都只存**文章引用**，不存 URL。引用写成
`<site>:<id>`（`rbook1:` = rbook.roj.ac.cn，`rbook2:` = rbook2.roj.ac.cn），渲染时由
`lib/rbook-articles.js` 从对应站点的 catalog 解析成标题和链接。

## 两个字段的分工

| 字段 | 语义 | 值格式 | 读者视角 |
| --- | --- | --- | --- |
| `showAtRbook` | 这道**题解**是 rbook 某篇文章的例题/练习，挂到文章下 | 字符串数组，元素是文章 id | rbook1 文章末尾的「相关题解」表格；rbook2 题目页的「RBook 文章」一行 |
| `rbookLinks` | 这道**题**要先掌握 rbook 里哪些知识，正向指出去 | 对象数组 `{ id \| url, label?, reason }` | 在题目详情页看到「相关知识」 |

判断标准：文章讲的知识**在本题之前**、值得读者先去看 → `rbookLinks`；文章拿这道题当
例子或练习、读者应该从文章过来 → `showAtRbook`。同一篇文章通常只落在一边，两侧都硬挂
会让读者绕圈。

`pre` / `common` / `recommend` 是题与题之间的关系，由
[`oj-problem-relation-writer`](../oj-problem-relation-writer/SKILL.md) 维护，不混写。

## 两个 rbook 站：id 必须带站点前缀

两本书都有目录接口，所以 `id` 形态两边都能用，但**必须带前缀**——两本书有 4 对同名不同文
的 id（`base`、`mst`、`minimal-string`、`other`），裸 id 无法区分，`lib/problem.js` 会直接
拒绝。

| | `newRbook_ejs`（`rainboyOJ/rbook`） | `rbook_nunjucks`（`rainboyOJ/rbook_nunjucks`） |
| --- | --- | --- |
| 线上 | `https://rbook.roj.ac.cn` | `https://rbook2.roj.ac.cn` |
| 形态 | 纯静态，`dist/` 里没有任何 `api*` | Node 服务，有 `/api/health`、`/api/catalog` |
| 文章身份 | md frontmatter 里**没有** `id:`；id 写在文章目录的 `config.yaml`（2026-11 起已统一，加载器仍兼容 `config.json/jsonc`；缺省时才由 `idFromPath()` 按目录名回退） | frontmatter 手写 `id:`（线上 447 篇 / 329 个模板） |
| 本地路径 | `~/mycode/newRbook_ejs`（`RBOOK2_CODE_PATH` **不**指向它） | `~/mycode/rbook_nunjucks/book` |

结论：

- **写 `id`，一律带前缀。** `rbook1:presum` 由构建期生成的 `/catalog.json` 解析；
  `rbook2:fhq-treap` 由 `/api/catalog` 解析。裸 id（`fhq-treap`）会直接报错。
- **`rbookLinks` 的 id 优先取 rbook1。** 同一篇文章两本都收时写 `rbook1:`；只有 rbook1
  里确实没有这篇、而 rbook2 有时才写 `rbook2:`。查找顺序因此固定为「先 rbook1，后 rbook2」，
  不要图省事直接抄 rbook2 的 id。
  两本书的 id 会漂：同一篇在 rbook2 叫 `binary-search`、在 rbook1 可能叫 `binary_search`；
  但**名字像不等于同一篇**——实测 `rbook1:binary_search` 在 `/recursion/binary_search/`
  （递归二分），`rbook2:binary-search` 在 `/base/binary_search/`（基础二分），是两篇。
  所以回 rbook1 找的时候要比 url 路径和正文，不能只比 id 相似度。
  反过来，`showAtRbook` 不适用这条偏好：它表示「哪篇文章拿本题当例题」，必须写真实
  收录了本题的那一篇，是哪本写哪本。
- **rbook1 的 id 在 `config.{json,jsonc,yaml,yml}` 里**（2026-11 已统一为 `config.yaml`：
  `book/` 下 132 个 yaml、0 个 json；旧格式仍可读），解析顺序是 `config.id` 优先、缺了才回落 `idFromPath()`
  （`src/publishing/content/metadata-normalizer.ts:23`）。两者会不一致：
  `book/data_structure/segment_tree/sgt_first_lt/config.yaml` 写的是 `id: sgt_lower_bound`，
  按目录名会拼成 `sgt_first_lt`。所以核对 rbook1 的 id 要读 config 或读 catalog.json，
  不要自己拼目录名。
- **两本 id 空间由前缀隔开**，`rbook1:base` 与 `rbook2:base` 是两篇不同的文章。
- `url` 形态是逃生口：站点目录里暂时查不到、或要深链到某个小节时才用，必须带 `label`。
- 尾斜杠实测：`/data_structure/heap/` 与 `/data_structure/heap/index.html` 都是 200，
  不带尾斜杠是 **301**——能打开，但探活时别把 301 当成失败或当成 200。

`id` 清单来源（三个入口，别另写扫描逻辑；`rbookLinks` 先跑 rbook1，找不到才跑 rbook2）：

| 用途 | 命令 |
| --- | --- |
| 线上真相（rbook1） | `python3 .../list_rbook_articles.py --book rbook1 --grep 前缀和` |
| 线上真相（rbook2） | `python3 .../list_rbook_articles.py --grep 二分` |
| 本地源码（rbook1，离线/未部署时） | `node ../rbook-idea-linker/scripts/list-rbook1-articles.mjs --grep 倍增` |

## 触发方式

**手动触发优先。** 用户点名要求更新 `showAtRbook` 或 `rbookLinks` 时，直接按本 skill 执行。

**交付后询问。** 在 [`oj-problem-workflow`](../oj-problem-workflow/SKILL.md) 走完一道题
的交付、进入「完成与报告」阶段时，问用户一句是否要顺便补这两个字段。用户不要求就跳过，
不自动写入。

不在这两个时机之外主动改这两个字段。

## 数据来源：rbook2 读本地书，rbook1 读目录

两本书的 id 出处不同：

- **rbook2**（`rbook_nunjucks`）：id 在本地 `book/pages/**/*.md` 的 frontmatter 里，读本地即可，
  不联网。
- **rbook1**（`newRbook_ejs`）：id 在文章目录的 `config.{json,jsonc,yaml,yml}` 里，线上对外清单
  是构建期生成的 `https://rbook.roj.ac.cn/catalog.json`。**优先用这份清单**，因为它等于部署
  真相；某个 id 在不在线上，以它为准。要离线核对（站点未部署、或对比源码改动）时，用
  [`rbook-idea-linker`](../rbook-idea-linker/scripts/list-rbook1-articles.mjs) 的本地扫描。

### 1. 定位 rbook2 的 book 目录

按顺序取第一个存在的：

1. 环境变量 `RBOOK2_CODE_PATH` 的值（它指向书目录根，即 `book.yaml` 所在目录）。
2. `~/mycode/rbook_nunjucks/book`。

两者都没有 `book.yaml` 时停下，报告「未找到 book.yaml」并询问用户书的位置。不要猜路径，
不要凭记忆编造 id。

### 2. 用脚本取可用文章清单

```bash
S=.agents/skills/showAtRbook-and-rbookLinks/scripts/list_rbook_articles.py

# rbookLinks：先查 rbook1
python3 $S --book rbook1 --grep 线段树 二分
python3 $S --book rbook1 --verify presum,binary_search
# rbook1 确实没有这篇，才查 rbook2
python3 $S --grep 线段树 二分
python3 $S --verify sgt-update-one,binary-search

python3 $S --book rbook1            # 全部 rbook1 文章（141 篇）
python3 $S --json                   # 机器可读（配合 --book 用）
```

**写文件前，两个字段里每个要写入的 id 都必须过一遍 `--verify`。** 这一步是硬要求：id 写错
时线上会静默丢掉链接，页面上什么都不显示，很难发现。

### 3. rbook2 为什么不能按 book.yaml 过滤，也不能裸扫 pages

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

### 4. rbook2 的 id 在文件里的位置

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
2. **先查 rbook1、再查 rbook2。** 用 `--book rbook1 --grep ...` 跑一轮关键词；rbook1 里没有
   你要的那篇时，再用默认的 rbook2 跑同样关键词。把候选收窄到 10 条以内，优先给真正讲同一
   算法或同一数据结构原理的文章，不要为了凑数把沾边的都列上。
3. **用 `ask_user` 多选让用户挑。** 每个选项写带前缀的 `id` 与 `title`，并给出挂载理由（为什么
   这道题属于这篇文章 / 为什么读者该先读这篇）。同时允许用户自由补充不在候选里的 id。
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
showAtRbook: ["rbook2:sgt-update-one"]
rbookLinks:
  - id: "rbook1:presum"                     # 首选 rbook1
    reason: "本题把区间和改成按位统计，先看这篇的前缀和"
  - id: "rbook2:sgt-value-first-less"       # rbook1 里没有这篇，退到 rbook2
    reason: "本题主解的线段树上跳跃就是这篇的模板"
  - url: "https://rbook.roj.ac.cn/data_structure/heap/#sift"   # 只有要深链小节时才用 url
    label: "堆（sift 部分）"
    reason: "本题用堆维护候选集，先看 sift 的实现"
pre: []
```

规则：

- `showAtRbook` 保持字符串数组，元素是 `<site>:<id>`，顺序即展示顺序。两个站点都能挂。
- 同一道题只登记一个 id：pcs2 里同时存在 roj 镜像（如 `roj/3225`「Cinema 电影」）和标准 OJ 号
  （如 `luogu/CF670C`「Cinema」）时，只给实际存在的那一条写 `rbook1:`，否则 rbook1 的
  「相关题解」表格里同一道题会出现两行。
- `rbookLinks` 元素必须**二选一**：写 `id`（带站点前缀）或写 `url`。不要两个都写，不要留空。
- `reason` 必填，一句话说清「为什么读这篇才能做本题」，不写「相关」「可参考」这类空话。
- `label` 可选：`id` 形态缺省时用 catalog 里的文章标题；`url` 形态**没有 catalog 可查**，
  必须写 `label`。
- **选哪种：先想 `id`。** 两本书的目录里能查到的都用 `id`——它能自动同步标题、坏链不显示、
  换域名不用改全库。只有目录里确实没有、或要深链到某个小节时才写 `url`。
- **写 id 时先 rbook1，后 rbook2。** rbook1 有这篇就写 `rbook1:<id>`；rbook1 没有、rbook2
  才有时写 `rbook2:<id>`，并在报告里说明「rbook1 查过没有」。
- 锚点：`id` 形态不带锚点（目录解析不认）；`url` 形态可以带 `#小节`，这也是需要深链时的
  唯一手段。
- 不要写 Markdown 链接（`[文字](url)`），字段里只有裸 URL。
- `updated` 刷成当前本地时间 `YYYY-MM-DD HH:MM`（首页按它排序），保留原 `date`；忘了刷不会被 `pre-push` 拦，只是「最后更新」列不准。
- 其余字段、正文、代码引用一概不动。
- 用户要清空时写 `showAtRbook: []` / `rbookLinks: []`。

## 校验

三件事按顺序做完，任何一步不过都要修：

1. **逐个核对 id**（两个字段的 id 合并去重后一起校验，按站点分开跑）：

```bash
python3 .agents/skills/showAtRbook-and-rbookLinks/scripts/list_rbook_articles.py --book rbook1 --verify <id1>,<id3>
python3 .agents/skills/showAtRbook-and-rbookLinks/scripts/list_rbook_articles.py --book rbook2 --verify <id2>
```

按站点分两次跑；前缀本身对不对由下一步把关。`rbookLinks` 里出现 `rbook2:` 时，顺手确认
rbook1 里是不是也有同一篇（有就该换成 `rbook1:`）。

`--verify` 会忽略前缀，只比对裸 id，所以按站点分两次跑；前缀本身对不对由下一步把关。

退出码非 0 说明有无效 id，不能交付。`--verify` 只管 `id` 形态；`url` 形态的条目要自己
确认能打开（`curl -s -o /dev/null -w '%{http_code}' <url>`；跟随便重定向，rbook1 的地址
带尾斜杠才是 200，不带是 301）。

2. **确认 YAML 能解析、`updated` 已刷新**，格式为 `YYYY-MM-DD HH:MM`：

```bash
python3 -c "import yaml,sys;d=yaml.safe_load(open(sys.argv[1]).read().split('---')[1]);print(d.get('showAtRbook'));print([x.get('id') for x in (d.get('rbookLinks') or [])])" problems/<oj>/<problem_id>/index.md
```

3. **跑目录检查**（前缀、`reason`、`id`/`url` 二选一由 `lib/problem.js` 归一化把关）：

```bash
python3 scripts/problem-analysis-tools/check_problem.py problems/<oj>/<problem_id>
```

批量任务最后统一跑 `npm run verify:push`，其中「rbook 文章链接」阶段会联网确认 id 真在
目录里（`npm run check:rbook-links`；只拉仓库里被引用到的站点，站点不可用即失败）。

批量任务把全库 `npm run check:content` 留给主 agent 统一跑；单题任务可以自己跑一次。

## 当前渲染状态（写之前知道）

两个字段都已接到页面，都由 `lib/rbook-articles.js` 解析：

- `showAtRbook` → 两本书都消费，落点不同：
  - **rbook1（newRbook_ejs）**：文章正文末尾自动生成 `## 相关题解` 表格（题目 | OJ | 难度），
    按 pcs2 `lib/difficulty.json` 的难度序排列，题目链到 pcs2 题解页。写进 `rbook1:` 的每一条
    都会真的出现在书上；id 写错则该行无声消失、不会报错，所以 `--verify` 必做。文章可用
    config 的 `practice: false` 关掉这一节。
  - **rbook2（rbook_nunjucks）**：题目页信息栏的「RBook 文章:」一行（反向：本文被哪篇文章当例题）。
- `rbookLinks` → 正文上方的**「前置阅读」卡片**，每条显示文章标题（新标签打开）与 `reason`
  全文小字，顺序即 frontmatter 数组顺序。解析不到的条目在页面上直接不显示，只在服务端 warn。
- `/api/problems/:oj/:id` 同时返回 `showAtRbook`（原始引用）与 `rbook_links`（已解析：
  `{site,id,title,url,reason}`）。
- 同一篇文章同时出现在两个字段里是允许的（方向不同），页面不做去重。

## 报告

简短说明：

- 改了哪个题目目录、写了哪个字段。
- 写入了哪些条目：`id` 形态给文章标题，`url` 形态给 `label` 与 200 校验结果，各自写理由。
- 保留 / 新增 / 移除了哪些原有条目。
- `--verify`、`url` 探活与 `check_problem.py` 的结果。
- 落到 `rbook2:` 的条目：rbook1 查过什么关键词、确实没有对应文章才退到 rbook2。
- 还有哪些候选没写入，以及原因（含「两本都没有，只能写 url」这类降级判断）。

## 不要做的事

- 不要凭记忆写 id：选题时用 `list_rbook_articles.py`（读线上 catalog）或
  `rbook-idea-linker` 的脚本（读本地源码）查真实 id。
- 不要按 `book.yaml` 过滤候选（会漏 60% 文章），也不要裸扫 `pages` 不过滤草稿（会写进
  无效 id）。
- 不要写 Markdown 链接（`[文字](url)`），字段里只有裸 URL。
- 不要给 `id` 形态加锚点，也不要把 rbook2 的文章写成 `url`（白丢标题同步和坏链检测）。
- 不要写裸 id：`id: "presum"` 会被 `lib/problem.js` 直接拒绝，必须 `rbook1:presum` 或
  `rbook2:presum`（两本是不同文章）。
- 不要编造文章 id 或标题。
- 不要改 `pre` / `common` / `recommend`；需要时提示转 `oj-problem-relation-writer`。
- 不要改题解正文、代码或图示。
- 用户没要求时不要自动写入这两个字段。
