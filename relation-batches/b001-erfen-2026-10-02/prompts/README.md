# 审核 Prompt 使用说明

三个验证点各对应一份 prompt，按顺序投喂给**独立的**审核 AI（建议开新会话，不带本批次的讨论上下文，避免被撰写者结论锚定）：

| 顺序 | 文件 | 输入 | 产出 | 何时执行 |
| --- | --- | --- | --- | --- |
| 1 | `01-topic-review.md` | `review-pack.md`（44 题） | `review-topic-verdicts.jsonl` | 第 2 步全量判断前 |
| 2 | `02-calibration-check.md` | `calibration.json`（9 对） | `review-calibration-verdicts.jsonl` | 与 1 同时做即可 |
| 3 | `03-post-write-audit.md` | `audit-sample.md`（写入后生成，随机 30 条） | `review-audit-verdicts.jsonl` | 写入完成后 |

## 为什么 prompt 要求写 jsonl

- 结论可以被脚本直接消费：我读取 jsonl 汇总进批次记录，不重新转述。
- 字段固定（verdict/agree/violated/evidence），防止审核 AI 用模糊措辞滑过判断。
- `evidence` 必须是原文短引——无证据的结论视为无效。

## 审核 AI 的独立性约定

- prompt 内置了与撰写者相同但**独立给定**的相似标准（三条件 + 宁可漏连不错连），标准原文来自方案文档，不是从我的结论反推的。
- Prompt 1/2 明确要求独立判断后再对照原标注，发现不一致必须报 `agree: false`。
- Prompt 3 明确「不因已写入而推定正确」。

## 与方案「用户最终判断」的关系

方案规定教学判断由用户最终裁定。AI 审核是**初审**：

- Prompt 1/2 的结论 → 用户扫一眼 `no`/`borderline`/不同意清单即可终审。
- Prompt 3 的 30 条抽查 → 门槛（≤1 条不通过）以 AI 初审计，用户可抽查 AI 的审核质量（例如随机看 5 条 AI 判 pass 的理由是否站得住）。
- 用户与 AI 结论不一致时，以用户为准，并记录进 `work-record.md`。
