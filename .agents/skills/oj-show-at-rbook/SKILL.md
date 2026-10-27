---
name: oj-show-at-rbook
description: >-
  为一道已完成的 OJ 题解维护 frontmatter 的 showAtRbook 字段：从本地 rbook 书读取
  真实存在的文章 id，按题目内容筛出候选，让用户挑选，再写回
  problems/<oj>/<problem_id>/index.md。用户要求「更新 showAtRbook」「把这道题挂到
  rbook 某篇文章下」「题解关联 rbook 文章」，或在题目交付后需要决定这个字段时使用。
  本 skill 只写 showAtRbook，不写 pre / common / recommend，不改题解正文，不生成图。
---

# 更新 showAtRbook

把一道题解挂到 rbook 书的相应文章下。这个字段决定题目详情页上的「对应 rbook 文章」链接。

本 skill 只负责 `showAtRbook` 一个字段。`pre` / `common` / `recommend` 是题与题之间的关系，由 [`oj-problem-relation-writer`](../oj-problem-relation-writer/SKILL.md) 维护，两者不混写。

## 触发方式

**手动触发优先。** 用户点名要求更新 `showAtRbook` 时，直接按本 skill 执行。

**交付后询问。** 在 [`oj-problem-workflow`](../oj-problem-workflow/SKILL.md) 走完一道题的交付、进入「完成与报告」阶段时，问用户一句是否要顺便更新 `showAtRbook`。用户不要求就跳过，不自动写入。

不在这两个时机之外主动改这个字段。

## 数据来源：只读本地书，不联网

文章 id 全部从本地 rbook 书取，不依赖线上服务。

### 1. 定位 book 目录

按顺序取第一个存在的：

1. 环境变量 `RBOOK2_CODE_PATH` 的值（它指向书目录根，即 `book.yaml` 所在目录）。
2. `~/mycode/rbook_nunjucks/book`。

两者都没有 `book.yaml` 时停下，报告「未找到 book.yaml」并询问用户书的位置。不要猜路径，不要凭记忆编造 id。

### 2. 用脚本取可用文章清单

```bash
S=.agents/skills/oj-show-at-rbook/scripts/list_rbook_articles.py

python3 $S --grep 线段树 二分        # 按关键词筛候选
python3 $S --verify sgt-update-one,binary-search   # 校验具体 id
python3 $S                          # 全部可用文章（约 444 篇）
python3 $S --json                   # 机器可读
```

**写文件前，每个要写入的 id 都必须过一遍 `--verify`。** 这一步是硬要求：`showAtRbook` 里写了不存在的 id，线上会静默丢掉链接，页面上什么都不显示，很难发现。

### 3. 为什么不能按 book.yaml 过滤，也不能裸扫 pages

两个坑，都实测过：

- **`book.yaml` 不是收录范围。** 它只是导航目录，只有 176 个条目，而书里实际可解析的文章有 445 篇。按 `book.yaml` 过滤会漏掉一大半可用文章。
- **裸扫 `book/pages/**/*.md` 会把草稿写进去。** `pages` 下有 470 个带 `id` 的 markdown，其中 25 个是草稿、TODO、草稿归档，它们不在任何目录里，线上也不生成页面。

脚本采用的判定规则（从 470 篇反向标定，与线上 445 篇对齐到 444 篇）：

> 候选 = `book/pages` 下所有带 frontmatter `id` 的 markdown，**排除**「所在目录名含『草稿』」或「文件名（不含扩展名）含 `草稿` / `todo` / `draft`」的文件。

已知的一处保守偏差：`graph-algorithm-book-note-archive`（路径 `Books/todo_图论与算法_程龚.md`）线上仍在目录里，但脚本按 `todo` 前缀把它排除了。这个偏差方向是安全的（少给候选，不会写出无效 id），遇到时用 `--all` 查看即可。

### 4. id 在文件里的位置

每篇文章在 `book/pages/**/index.md` 的 frontmatter 里：

```yaml
---
id: "sgt-update-one"
title: "线段树：单点修改与区间查询"
---
```

`id` 可能是 `index.md`，也可能在 `草稿/` 之外的任意 md 文件里（例如 `Books/xxx.md`、`data_structure/segment_tree/other.md`），所以脚本按 `rglob('*.md')` 扫，不要只找 `index.md`。

## 交互：先搜再选

文章有几百篇，不能整表铺给用户。

1. **从当前题提炼关键词。** 读当前题 `index.md` 的 `tags`、`title`、`description`，加上正文讲到的核心算法名。线段树题会得到 `线段树`、`二分`、`区间最值`、`sgt`、`binary-search`。
2. **用 `--grep` 多跑几个关键词**，把候选收窄到 10 条以内。优先给真正讲同一算法或同一数据结构原理的文章，不要为了凑数把沾边的都列上。
3. **用 `ask_user` 多选让用户挑。** 每个选项写 `id` 与 `title`，并给出挂载理由（为什么这道题属于这篇文章）。同时允许用户自由补充不在候选里的 id。
4. **校验用户手填的 id**，不在可用清单里就明确告知「这个 id 不在可用范围内（可能是草稿或拼错）」并让用户改选。不要直接写入。
5. **保留已有值。** 当前 `showAtRbook` 非空时，把已有 id 一并展示，让用户决定保留、增补还是替换。不要静默覆盖。

用户明确说「你自己判断」时才跳过第 3 步，但仍要把最终选择列出来让用户确认。

判断挂载理由时的分寸：优先选**讲同一数据结构 / 同一算法原理**的文章。只是用到同一个词（比如都出现「线段树」但一篇讲扫描线、一篇讲树上二分）不算强关联。倒过来的情形也不强求——比如一道维护下标线段树区间最大值的题，和一篇讲值域线段树查第一个小值位置的文章，骨架同源但语义相反，可以作为「对照」挂上，但不要写成前置。

## 写入

只改 `problems/<oj>/<problem_id>/index.md` 的 frontmatter：

- `showAtRbook` 是字符串数组，元素为文章 id。
- 字段顺序按 [`oj-problem-format-spec`](../oj-problem-format-spec/references/frontmatter.md)：在 `categories` 之后、`pre` 之前。
- `updated` 刷成当前本地时间 `YYYY-MM-DD HH:MM`，保留原 `date`。
- 其余字段、正文、代码引用一概不动。

```yaml
categories: []
showAtRbook: ["sgt-update-one", "sgt-value-first-less", "binary-search"]
pre: []
```

用户要清空时写 `showAtRbook: []`。

## 校验

三件事按顺序做完，任何一步不过都要修：

1. **逐个核对 id**：

```bash
python3 .agents/skills/oj-show-at-rbook/scripts/list_rbook_articles.py --verify <id1>,<id2>,...
```

退出码非 0 说明有无效 id，不能交付。

2. **确认 `updated` 已刷新**，格式为 `YYYY-MM-DD HH:MM`。

3. **跑目录检查**：

```bash
python3 scripts/problem-analysis-tools/check_problem.py problems/<oj>/<problem_id>
```

批量任务把全库 `npm run check:content` 留给主 agent 统一跑；单题任务可以自己跑一次。

## 报告

简短说明：

- 改了哪个题目目录。
- 写入了哪些 id 与对应文章标题，各自挂载理由。
- 保留 / 新增 / 移除了哪些原有 id。
- `--verify` 与 `check_problem.py` 的结果。
- 还有哪些候选没写入，以及原因。

## 不要做的事

- 不要联网拉 catalog 或依赖线上服务。
- 不要按 `book.yaml` 过滤候选（会漏 60% 文章），也不要裸扫 `pages` 不过滤草稿（会写进无效 id）。
- 不要编造文章 id 或标题。
- 不要改 `pre` / `common` / `recommend`；需要时提示转 `oj-problem-relation-writer`。
- 不要改题解正文、代码或图示。
- 用户没要求时不要自动写入这个字段。
