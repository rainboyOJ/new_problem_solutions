---
name: oj-problem-relation-writer
description: Maintain prerequisite, similar-problem, and external recommendation metadata in OJ problem index.md frontmatter. Use this skill when the user asks to add pre/common/recommend relations, 前置题目, 类似题目, common problems, 推荐练习, 跨 OJ 推荐, learning path metadata, or problem graph relation data. This skill only writes relation/recommend metadata and candidate notes; it does not write problem analysis content and does not render graphs.
---

# OJ 题目关系维护

这个 skill 专门负责维护题目之间的学习关系和跨 OJ 练习推荐，把高置信度关系写入当前题目的 `index.md` frontmatter。

它只负责关系元数据，不负责：

- 写题目解析正文。
- 修改 `main.cpp` / `brute.cpp` / `gen.py`。
- 生成或渲染前端图，或改 vis-network 等可视化代码。
- 把低置信度候选强行写进正式 frontmatter。

## 目标

为每道题补充三类关系（完整字段示例见 [`references/frontmatter-examples.md`](references/frontmatter-examples.md)）：

- `pre`：当前题的前置题。前置题更简单，并且包含当前题的一部分核心思想、模型或算法。
- `common`：和当前题相似的题。它们不一定更简单，但解法模型、状态设计、核心观察或训练目标相似。
- `recommend`：仓库外或跨 OJ 的继续练习推荐，例如 Luogu、Codeforces、HDU、POJ、LeetCode、USACO、AtCoder 等。

`pre` / `common` 由 render/frontend 程序读取，用于展示题目学习图。`recommend` 由题目详情页展示为“推荐练习”，暂不进入关系图。

## 字段规则

`pre` / `common` 都是对象数组，元素必须有 `oj` 和 `problem_id`：

- `oj` 必须使用仓库中对应题目 frontmatter 的 `oj`。
- `problem_id` 必须优先使用目标题 `index.md` frontmatter 中的 `problem_id`；目标文件不存在或无法读取时，才用目录名作为临时候选。
- `reason` 可选，但强烈推荐填写一句简短中文原因，方便图谱 tooltip 和人工复查。
- 不使用 `pid`，本仓库统一用 `problem_id`。
- 不引用当前题自己，不写重复关系。

`recommend` 数组项必须有 `oj`、`problem_id`、`reason`、`relation`：

- `title` 推荐填写，不知道时用空字符串。
- `url` 对外部 OJ 强烈推荐填写；无法验证就放入候选，不写正式 `recommend`。
- `relation` 只能是 `similar`（同模型或高度相似）、`practice`（后续练习）、`harder`（进阶）、`easier`（热身）。
- 推荐题已经在本仓库 `problems/` 中时，优先写 `pre` / `common`，不要重复写 `recommend`。

## 图语义

以当前题 `A` 为例：

- `pre` 是有向边 `luogu/P1002 -> A`，从前置题指向当前题；沿箭头方向就是推荐学习路线。
- `common` 不表示学习依赖方向（`A -- B`），前端可渲染成无向边或双向虚线边；本 skill 不决定渲染方式。
- `recommend` 不参与关系图（`A --external practice--> external problem`），只进题目详情页的“推荐练习”列表。

## 关系判断标准

### `pre`

只在同时满足这些条件时写入 `pre`：

- 目标题明显更简单或更基础。
- 目标题包含当前题的一部分核心思想、模型、算法或实现技巧。
- 学完目标题能降低理解当前题的难度。
- 关系方向清楚：目标题是当前题的前置，而不是反过来。

常见例子：一维 DP 是二维 DP 的前置；普通网格路径计数是带障碍/特殊限制网格路径计数的前置；BFS 基础题是带状态压缩 BFS 的前置；前缀和基础题是区间统计优化题的前置。

### `common`

只在解法结构或训练目标确实相似时写入 `common`：

- 使用相同核心模型，例如区间 DP、树形 DP、最短路、二分答案、双指针。
- 状态设计或转移方式高度相似，或关键观察相似。
- 适合放在同一组里对比训练。

`common` 不要求难度更低。

### `recommend`

只在满足这些条件时写入正式 `recommend`：

- 题目不在当前仓库中，或暂时无法作为仓库内 `pre` / `common` 关系引用。
- 题目的 OJ、题号、标题和 URL 能被用户提供或联网验证。
- 与当前题存在明确训练价值，例如同模型练习、进阶版本、热身版本。
- `reason` 能用一句中文说明推荐原因。

不要凭记忆编外部题链接。需要跨 OJ 推荐时允许联网验证；无法验证的只写入候选。

### 候选关系

只是标签相同、题面表面相似、或无法确认难度/核心思想的关系，不写入 `index.md`，记录到 `problems/<oj>/<problem_id>/problem-relation-workspace/candidates.md`（记录格式见 [`references/frontmatter-examples.md`](references/frontmatter-examples.md)）。

## Source Priority

判断关系时按这个顺序读取信息：

1. 当前题 `index.md` frontmatter 和正文。
2. 当前题 `main.cpp`、`brute.cpp`、`problem.md`。
3. 当前题 `problem-analysis-workspace/*.md`，如果存在。
4. 候选题 `index.md` frontmatter 和正文，以及候选题的代码与题面。
5. 仓库搜索结果，例如 `tags`、标题、正文关键词。
6. 用户明确给出的关系或解释。
7. 需要跨 OJ 推荐时，联网验证外部题目的 OJ、题号、标题和 URL。

如果用户明确指定某个关系，仍然要检查是否引用自己、是否目标存在、字段格式是否正确。

## Search Workflow

当用户没有给出具体前置题或相似题时：

1. 先理解当前题的核心模型和标签。
2. 用 `rg` 搜索仓库中同标签、同模型、同关键词的题目。
3. 优先检查更简单、基础、经典的题。
4. 对每个候选判断是 `pre`、`common`，还是只写入 candidates。
5. 对仓库外继续练习题，验证后写入 `recommend`；不确定时写入 candidates。
6. 只把高置信度关系写入 frontmatter；没有高置信度关系时保留 `pre: []` / `common: []` / `recommend: []`。

不要为了填满字段而强行找关系。

## Frontmatter Update Rules

- 只修改 YAML frontmatter 中的 `pre` / `common` / `recommend`，除非用户明确要求整理其他字段。
- 保留已有准确关系和 `favorite` / `favorite_reason` 个人学习元数据（收藏原因不写入 `tags`），保留原有正文不变。
- 删除重复关系；不删除已有关系，除非确认它错误或用户要求删除。
- 字段顺序遵守 `oj-problem-format-spec`：`pre`、`common` 放在 `categories` 后、`source` 前。
- 字段不存在时新增；完整片段见 [`references/frontmatter-examples.md`](references/frontmatter-examples.md)。

## Consistency Check

交付前先确认「字段规则」全部满足，然后检查：

- `pre` 的关系方向是 `pre_problem -> current_problem`；`common` 不被描述为前置依赖。
- 关系目标尽量能在仓库中找到对应 `problems/<oj>/<problem_dir>/index.md`；`problem_id` 与目标 frontmatter 一致，目录名和 frontmatter 不同时以 frontmatter 为准。
- `recommend.url` 尽量填写已验证链接，缺失时应说明原因。
- 低置信度候选没有写入正式 frontmatter。

## Verification Script

更新 `pre` / `common` 后，优先运行关系校验脚本（三种调用方式见 [`references/frontmatter-examples.md`](references/frontmatter-examples.md)）：

```bash
python3 scripts/problem-analysis-tools/check_relations.py problems/<oj>/<problem_id>
```

这个脚本只做校验，不自动推荐关系、不修改 frontmatter、不生成图。如果脚本没有运行，最终回复必须说明原因。

## Safety Rules

- 不要编造不存在的题目。
- 不要仅凭同一个 tag 写入关系。
- 不要把所有同类题都写成 `common`，只写真正有训练价值的相似题。
- 不要凭记忆写外部 OJ 推荐链接；正式 `recommend` 需要可验证来源。
- 不要把仓库内已存在题重复写进 `recommend`。
- 不要写题解正文。
- 不要改前端或图渲染代码。
- 不要把候选关系说成已确认关系。
- 不要 claim 图已经生成或渲染，除非用户另行要求并且实际完成。

## Final Response

完成后简短报告：

- 更新了哪个题目目录。
- `pre` / `common` / `recommend` 各写入了哪些关系。
- 是否创建或更新了 `problem-relation-workspace/candidates.md`。
- 是否运行了 `check_relations.py`，结果如何。
- 有哪些候选没有写入 frontmatter，以及原因。
- 是否发现引用目标不存在或需要用户确认。
