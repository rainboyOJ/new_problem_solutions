# Prompt 3/3：写入后抽查（随机 30 条新增关系）

> 用法：第 2 步写入完成后使用。我会先生成 `audit-sample.md`（随机种子已记录）。
> 复制本 prompt 给审核 AI 并附上/让它读取 `audit-sample.md`。
> 验收门槛（方案已定）：30 条中**最多允许 1 条**不符合标准，才算本批可扩展；发现的错误一律修正。

---

你是一名 OJ 题目关系抽查员。仓库刚由 AI 批量新增了一批「相似题」关系（`common`，写入各题 `index.md` 的 frontmatter）。你抽查其中随机 30 条，逐条裁定：**这条关系是否符合相似标准、reason 是否被材料支持**。你的结论决定这批写入是否通过验收。

## 输入

- 仓库根目录：`/Users/rainboymac/mycode/RBOOK_series/pcs2-problem-relation`
- 抽查清单：`relation-batches/b001-erfen-2026-10-02/audit-sample.md`
  （每条含：两题身份、写入的 `reason`、判断时使用的材料位置、随机种子）
- 核对原文：两题的 `problems/<oj>/<problem_id>/index.md`（含 frontmatter 中已写入的 `common`）
  与材料 `relation-batches/b001-erfen-2026-10-02/materials/<oj>__<problem_id>.md`

## 相似标准（须同时满足，否则 `fail`）

1. 核心模型相同（如都是「最大化最小值 + 单调判定」的二分答案、都是分数规划）。
2. 判定过程或状态设计高度相近（check/状态转移结构可互相套用）。
3. 关键观察可迁移（对比训练有实际收益）。

**以下算 `fail`**：只共享二分答案等通用技巧；仅标签/背景相似；reason 与题解原文不符或查无实据；把模板题与其无关的综合题硬连。

## 每条的检查动作

1. 读两题题解，各自用一句话概括：核心模型 / 判定过程 / 关键观察。
2. 对照写入的 `reason`：reason 声称的共同点是否在两题原文中都有依据？（reason 是外围流程撰写的，不是模型生成的解释，同样要核对。）
3. 用三条件裁定：
   - `pass`：三条件满足，reason 有据
   - `fail`：任一条件不满足，或 reason 与原文不符（写明哪一条不满足）
   - `uncertain`：材料不足以裁定（按不通过计，写明缺什么材料）
4. **独立判断**：不要因为「已经写入了」就推定它正确；也不要为了显示审核价值而苛求——标准就是上面三条。

## 输出

1. 逐条写入 `relation-batches/b001-erfen-2026-10-02/review-audit-verdicts.jsonl`，每行：

```json
{"pair_id": "w007", "a": "luogu/P1873", "b": "POJ/3122", "verdict": "pass", "reason_check": "reason 与两题判定结构一致", "violated": [], "evidence_a": "二分锯片高度+求和判定", "evidence_b": "二分体积+计数判定"}
```

- `verdict`：`pass` / `fail` / `uncertain`
- `violated`：不满足的条件编号列表（如 `["2"]`），`pass` 时为 `[]`
- 30 条全部输出，不允许跳过

2. 回复汇总（不逐条罗列）：

```
抽查完成：pass N / fail N / uncertain N
失败清单：<pair_id + 违反的条件 + 一句原因>
验收结论：<通过（≤1 条不通过）/ 不通过，建议撤销或修正本批>
共性问题：<无 或 如「reason 普遍夸大判定结构相似度」>
```

## 后续（不由你执行，仅告知）

抽查结论由用户最终裁定；不通过时本批将修正或撤销（按 `writes.jsonl` 只删除本批新增项），不得扩大规模。
