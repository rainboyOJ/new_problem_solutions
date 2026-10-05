# Prompt 2/3：校准标注复核（9 对人工标注是否正确）

> 用法：复制给审核 AI。目的：复核 `calibration.json` 中 9 对题的 `expected` 标注。
> 特别重要：4 个陷阱对（c06–c09）的定性直接决定「相似标准」的松紧，必须独立判断。

---

你是一名 OJ 题目相似关系审核员。仓库正在批量补充「相似题」关系（`common`），并用 9 对人工标注的题对校准判断阈值。你的任务是**独立复核这 9 对的标注是否符合下述相似标准**。你的结论若与原标注不同，将直接改变批量写入的门槛，请给出可核查的理由。

## 输入

- 仓库根目录：`/Users/rainboymac/mycode/RBOOK_series/pcs2-problem-relation`
- 标注文件：`relation-batches/b001-erfen-2026-10-02/calibration.json`（`expected` + `note`）
- 每题材料：`relation-batches/b001-erfen-2026-10-02/materials/<oj>__<problem_id>.md`（原文摘录）
- 需要更多上下文时读 `problems/<oj>/<problem_id>/index.md` 及其代码。

## 相似标准（`common` 的写入条件，须同时满足）

1. **核心模型相同**：如都是「最大化最小值 + 单调判定」的二分答案、都是分数规划。
2. **判定过程或状态设计高度相近**：两题的 check 函数/状态转移结构可以互相套用。
3. **关键观察可迁移**：一题的解题思路搬到另一题基本成立，放在一起对比训练有收益。

**以下一律不算相似**：都使用二分答案这个通用技巧；标签或故事背景相同；一题是模板题而另一题只是包含该技巧的综合题；只是难度接近。

取舍原则：**宁可漏连，不错连**。证据不足时判 `not_common` 或 `uncertain`，不要为了覆盖率放宽标准。

## 工作方式

- 逐对独立判断，禁止因为「同为二分答案专题」而预设相似。
- 每个结论必须引用两题材料中的具体依据（各自的核心模型/判定结构是什么）。
- 先自己给每对定性，再对照 `expected`；不一致时明确写 `agree: false` 并说明哪个标注错了、为什么。

## 输出

1. 逐对结论写入 `relation-batches/b001-erfen-2026-10-02/review-calibration-verdicts.jsonl`，每行：

```json
{"pair_id": "c06", "my_label": "not_common", "agree": true, "evidence_a": "二分体积+贪心计数切块", "evidence_b": "二分比值+0/1背包判定", "reason": "判定结构不同，关键观察不可迁移", "confidence": "high"}
```

- `my_label`：`common` / `not_common` / `uncertain`
- `agree`：与 `calibration.json` 的 `expected` 是否一致（`uncertain` 视为 `agree: false` 并在 reason 说明）
- `confidence`：`high` / `medium` / `low`
- 9 对全部输出，不允许跳过

2. 回复汇总（不逐对罗列）：

```
校准复核完成：同意 9 对 / 不同意 N 对
不同意清单：<pair_id + 我的定性 + 一句原因>
陷阱对（c06–c09）是否确实不该连边：<是/否 + 一句总结>
```
