# Frontmatter 规范

题解文件必须以 YAML frontmatter 开头。新建文章推荐使用以下顺序：

```yaml
---
oj: "luogu"
problem_id: "P1001"
title: ""
description: ""
difficulty: "未知"
date: 2025-11-28 15:41
updated: 2025-11-28 15:41
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
rbookLinks: []
pre: []
common: []
recommend: []
source:
---
```

字段含义和维护边界：

- `oj` 用小写 OJ 名称，通常等于目录名；`problem_id` 始终是字符串。
- `title`、`source` 不确定时留空，不编造。
- `description` 是一行核心解法摘要，最多 120 字，不设字数下限。新建或最终写作必须非空，格式修正旧文无法判断时可为空。本仓库正式写法是由 `oj-distill-problem` 产出的“关键思维动作链”：2～4 项，各项用 ` + ` 连接，例如 `最后出现位置跳过无效过程 + 按位置统计贡献 + 沿依赖拓扑累加`。不写题面背景、不写“经典题/详见下文”等空话，也不写成正文摘要或算法标签列表。
- `difficulty` 使用 `入门`、`普及-`、`普及`、`普及+/提高-`、`提高`、`提高+/省选-`、`省选/NOI-`、`未知`。新建模板为 `未知`，最终文章应尽量评估，不能可靠判断时保留 `未知`。
- `date` 新建使用本地当前时间，修改旧文保留原日期；`toc` 固定为 `true`。
- `updated` 是“最后修改时间”，格式与 `date` 相同（`YYYY-MM-DD HH:MM`），必须紧跟 `date` 之后。新建时等于 `date`。首页默认按它降序排列，「最后更新」列也显示它。`pre-push` 只要求本次 push 改动到的题目目录里 `updated` 存在且格式合法（新增题也算），**不比较新旧**：日常改题顺手刷成当前时间是为了让展示准确，批量维护（一次改上百个目录）不刷也不会被拦。旧题缺少该字段时，`npm run check:content` 会报错（可从 Git 历史回填：`python3 scripts/migrate-add-problem-updated.py --apply`）。
- `tags`、`categories` 为数组。本格式 skill 只保证类型和顺序，具体算法标签由写作流程根据仓库已有标签选择。
- `favorite` 必须是布尔个人标记，`favorite_reason` 必须是字符串；新建默认 `false` 和空字符串，修改旧文保留有效值。
- `showAtRbook` 是可选数组，元素为**带站点前缀**的 rbook 文章引用（`rbook2:fhq-treap`、`rbook1:presum`），表示本题解要挂到哪些 rbook 文章下；新建默认空数组。前缀必须写：两本书有 4 对同名不同文的 id（`base`、`mst`、`minimal-string`、`other`），裸 id 会被归一化直接拒绝。题解内容写完后由 [`oj-show-at-rbook`](../../oj-show-at-rbook/SKILL.md) 维护（它从 rbook 目录取真实 id 并校验）；不要凭记忆填写。
- `rbookLinks` 是可选对象数组，表示本题解**正向指向**的 rbook 知识文章：读者做本题前应先看的原理。每个元素是 `{ id | url, label?, reason }`：
  - `id`：`<site>:<id>` 形式，首选形态。`rbook1:presum` 走 `https://rbook.roj.ac.cn/catalog.json`（构建期生成的文章清单），`rbook2:fhq-treap` 走 `https://rbook2.roj.ac.cn/api/catalog`。标题从目录同步，id 无效时不显示，换域名不用改全库。**一篇两本都收时优先写 `rbook1:`**；rbook1 里没有、rbook2 才有时才写 `rbook2:`。
  - `url`：逃生口，只在目录里确实查不到、或要深链到某个小节时使用，必须写 `label`。
  - `id` 与 `url` 二选一，不共存；`label` 只有 `url` 形态必填（且 `id` 形态写了会报错）；`reason` 始终必填，写清「为什么读这篇才能做本题」，不写「相关」「可参考」这类空话。
  - `id` 形态不带锚点，`url` 形态可以带 `#小节`。不要写 Markdown 链接。

  新建默认空数组。由 [`oj-show-at-rbook`](../../oj-show-at-rbook/SKILL.md) 维护并校验（rbook2 读本地书、rbook1 读线上 `/catalog.json`，并说清两站的 id 差异：优先 `rbook1:`）。
- `showAtRbook` 与 `rbookLinks` 的区别是方向：文章拿本题当例题/练习用 `showAtRbook`；本题拿文章当前置知识用 `rbookLinks`。同一篇文章通常只落一边。
- `pre`、`common`、`recommend` 为可选数组。新建题解应包含空数组；旧文没有时，格式修正不强制添加。具体关系和外部推荐交给 `oj-problem-relation-writer`。

若关系字段存在，顺序为 `categories`、`showAtRbook`、`rbookLinks`、`pre`、`common`、`recommend`、`source`。关系元素格式示例：

```yaml
rbookLinks:
  - id: "rbook2:sgt-value-first-less"
    reason: "本题主解的线段树上跳跃就是这篇的模板"
  - id: "rbook1:presum"
    reason: "本题把区间和改成按位统计，先看这篇的前缀和"
  - url: "https://rbook.roj.ac.cn/data_structure/heap/#sift"
    label: "堆（sift 部分）"
    reason: "本题用堆维护候选集，先看这篇的堆实现"
pre:
  - oj: "luogu"
    problem_id: "P1002"
    reason: "网格路径计数 DP 的基础版本"
recommend:
  - oj: "leetcode"
    problem_id: "62"
    title: "Unique Paths"
    url: "https://leetcode.com/problems/unique-paths/"
    reason: "同模型练习"
    relation: "similar"
```

难度获取优先级：洛谷使用 `python3 scripts/problem-analysis-tools/fetch_problem.py luogu <problem_id> --json` 的官方 `difficulty`：`0` 到 `7` 依次对应上述八档；其他 OJ 使用可靠的官方 rating 换算，无法判断才按复杂度和知识点估计。不要凭记忆编造难度。
