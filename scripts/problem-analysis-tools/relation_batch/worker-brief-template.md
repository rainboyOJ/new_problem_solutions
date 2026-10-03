# pre 关系裁定任务书模板（批次 {{BATCH}}）

> 派发时替换全部 `{{...}}` 占位符。**一个 worker 只判一个候选对**，判完写结果文件即结束，不要创建下级 agent。

## 你的唯一产物

只写这一个文件（目录不存在就创建，**不要写别的文件**）：

```text
{{RESULT_PATH}}
```

一行一份 JSON，符合 `scripts/problem-analysis-tools/relation_batch/worker-result.schema.json`。
**不要修改任何题目文件、不要运行 git、不要写批次台账。** 改题目和 Git 只有主 agent 能做。

## 本任务

| 项 | 值 |
| --- | --- |
| task_id | `{{TASK_ID}}` |
| attempt | `{{ATTEMPT}}` |
| 题对 key | `{{PAIR_KEY}}` |
| A（较简单，前置候选） | `{{A_KEY}}`（`{{A_DIR}}/index.md`） |
| B（较难，接收端） | `{{B_KEY}}`（`{{B_DIR}}/index.md`） |
| 材料摘录 | `{{MATERIAL_DIR}}/{{A_FILE}}`、`{{MATERIAL_DIR}}/{{B_FILE}}` |
| 证据 hash | A `{{A_HASH}}` / B `{{B_HASH}}` |
| 提示词版本 | `pre-v6` / 规则版本 `{{RULE_VERSION}}` |

## 必读

1. **两题 index.md 原文全文**（`{{A_DIR}}/index.md`、`{{B_DIR}}/index.md`）。
   `materials/` 里的摘录在 4000 字符处截断，**不足以作结论时必须补读原文全文**。
2. B 的引用代码（`main.cpp`、`brute.cpp` 等，路径见材料末尾「代码位置」）与 `problem.md`（若存在）。
3. 需要时读 `{{A_DIR}}/main.cpp` 等 A 的代码，确认 A 到底教了哪一步。
4. 多解法时，**必须指明 B 的哪一种解法**复用了 A 的步骤。

## 判定口径（严格，三条必须同时满足）

1. **台阶性**：A 是相对简洁的模板/基础题，B 在 A 的基础上叠加额外流程。
2. **真实复用**：A 教过的**具体**判定、状态设计或关键观察，确实是 B 解法中**实际使用的一步**。
   —— 仅共享「都用二分答案」「都属 DP」这类通用框架**不算**。
3. **方向正确**：A 更基础，B 更难更综合。本次窗口为 `1 <= rank(B) - rank(A) <= 2`
   （难度序：入门 < 普及- < 普及 < 普及/提高- < 普及+/提高- < 普及+/提高 < 提高 < 提高+/省选- < 省选/NOI- < NOI/NOI+/CTSC）。

**必须排除**：同难度孪生题（应写 `common`）、B 的主要难度是 A 未教的新范式、方向颠倒。

## 输出字段

| 字段 | 要求 |
| --- | --- |
| `verdict` | `accept` / `reject` / `doubtful`（证据不足或边界用 doubtful，**不强迫二选一**） |
| `reject_reason` | `reject` 时必填，枚举：`same-difficulty-twin` / `b-difficulty-elsewhere` / `no-reuse` / `direction-wrong` / `insufficient-evidence` / `self-or-duplicate` |
| `a_step` | A 里被复用的那一步（一句中文，含关键词，≤40 字） |
| `b_use` | B 里用到它的那一步（一句中文，含关键词，≤40 字） |
| `quote_a` | A 原文**逐字**片段，不得改写。长度折算 ≤24（中文字数 + ASCII字符数/4）；一行代码可以，整段不行 |
| `quote_b` | B 原文**逐字**片段，不得改写。长度折算 ≤24（中文字数 + ASCII字符数/4）；一行代码可以，整段不行 |
| `src_a` / `src_b` | 形如 `problems/luogu/P1873/index.md:44`，行号必须是引文实际所在行 |
| `reason` | **一句话说明具体迁移关系**，必须含 `a_step` 或 `b_use` 里的关键词 |
| `strength` | `accept` 时必填：`strong`（B 的代码/证明里能指认该步骤）或 `template-level`（只是模板级复用） |
| `confidence` | `high` / `medium` / `low` |
| `task_id` / `attempt` / `model` | 按上面表格与你的实际模型填写 |

**约束**：引文必须来自题目原文的**题意/思路/证明/代码**，不得引用已有 `pre`/`common` 的
`reason` 反推关系成立。关键词命中不会自动让关系升级为 accept——语义成立与否由你负责。

## 输出示例（一行）

```json
{"task_id":"{{TASK_ID}}","attempt":{{ATTEMPT}},"key":"{{PAIR_KEY}}","verdict":"accept","reject_reason":"","a_step":"变号区间内二分求零点","b_use":"扫描根区间后逐区间复用同一二分","quote_a":"若区间两端函数值异号则其中必有根","src_a":"{{A_DIR}}/index.md:41","quote_b":"在每个变号区间内二分逼近实根","src_b":"{{B_DIR}}/index.md:63","reason":"B 把 A 教的变号区间二分逐区间套用，只是从单根扩到三次方程的三个根","strength":"strong","confidence":"high","model":"small-sheep/deepseek-v4.1-flash"}
```

## 完成

把结果追加写入 `{{RESULT_PATH}}` 后，输出一行：

```text
DONE {{PAIR_KEY}} <verdict>
```
