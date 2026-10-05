# relation_batch：题目相似关系（common）批处理工具

实现 [docs/plans/jev-problem-similarity-batch.md](../../../docs/plans/jev-problem-similarity-batch.md)
的批处理基础设施：专题清单与基线、候选题对生成、判断材料摘录、Jev 校准与结果记录。
关系写入本身遵循 `oj-problem-relation-writer` skill 的字段与安全规则，本工具只负责
「候选 → 判断 → 记录」，写入前仍需人工确认与抽查。

## 组成

| 文件 | 作用 |
| --- | --- |
| `batch.py` | 批处理 CLI：`init` / `pairs` / `materials` / `calibrate` / `report` |
| `jev_client.py` | Jev（TypeSafe System One）HTTP 客户端：多问题并行、429 退避、原始返回落盘 |
| `questions-common-v1.json` | 判断问题模板（提示词与规则版本，随批次记录留档） |

Jev 接入（2026-10-02 实测）：

- 端点 `POST https://opencode.ai/zen/v1/systemone`，模型 `jev-1.13-free`，免 Authorization。
- 非 OpenAI 格式：没有 `messages`；`/chat/completions`、`/responses` 会 500。
- `choice` criteria 最多 255 项；`score` 2–10 级；`state` + 全部问题 ≤ 32k token。
- 端点前置 Cloudflare 拦截 Python 默认 UA，客户端已改用常规 UA。
- 付费模型 `jev-1.13` 需 `Authorization: Bearer $OPENCODE_API_KEY`（zen workspace）。

## 批次目录布局

```text
relation-batches/<batch-id>/
├── manifest.json             基线：题目身份（frontmatter oj/problem_id）、内容哈希、
│                             已有关系、筛查结论、git 状态、模型与模板版本
├── problems.md               人类可读清单（含待人工确认项）
├── excludes.json             人工排除 [{dir, reason}]（关键词命中≠入选，人工可否决）
├── pairs.jsonl               待判断无序题对
├── pairs-excluded.jsonl      排除题对及原因（已有 common / 疑似同一题目）
├── materials/<oj>__<pid>.md  判断材料摘录（原文+来源位置，非模型摘要）
├── calibration.json          人工标注校准题对（expected 为撰写者初判，用户最终裁定）
├── calibration-results.jsonl 校准结果（含 usage）
├── raw/*.json                每次 Jev 请求的 payload + 原始返回（可追溯性）
└── work-record.md            批次工作记录（用量、费用、结论、抽查、撤销信息）
```

## 使用

```bash
cd <repo root>
# 1. 建批：专题候选清单与基线（关键词检索全文，自动筛查完整性）
python3 scripts/problem-analysis-tools/relation_batch/batch.py init \
    --batch b001-erfen-2026-10-02 --topic 二分答案

# 2. 生成无序候选题对（自动排除自身、重复题对、已有 common、疑似同一题目）
python3 scripts/problem-analysis-tools/relation_batch/batch.py pairs --batch b001-erfen-2026-10-02

# 3. 生成判断材料摘录（可 --only 限定题目）
python3 scripts/problem-analysis-tools/relation_batch/batch.py materials --batch b001-erfen-2026-10-02

# 4. 校准：用人工标注题对跑 Jev，输出阈值建议（先小样本，再全量）
python3 scripts/problem-analysis-tools/relation_batch/batch.py calibrate --batch b001-erfen-2026-10-02

# 状态汇总
python3 scripts/problem-analysis-tools/relation_batch/batch.py report --batch b001-erfen-2026-10-02
```

## 判断与合并规则

每个题对把两题材料放进 `state`（命名字段 `problem_A` / `problem_B`），一次请求并行问
`questions-common-v1.json` 中的 4 个窄判断（Noul）：

- `shared_core`：是否共享核心算法模型（不只是都用了某个通用技巧）
- `check_similar`：判定过程/状态设计是否高度相近
- `observation_transfer`：关键观察能否迁移（有对比训练价值）
- `only_label`：相似性是否仅来自通用标签/故事背景

合并为「写入 / 不写入」由明确规则完成（阈值由校准实验确定）。
**Jev 不生成解释**：`reason` 由外围流程根据材料撰写并标注依据，不伪称为模型解释。

## 安全边界

- 只新增 `common`，保留已有关系与正文；不写 `pre` / `recommend`（本阶段）。
- 只对通过筛查 + 人工确认的题目写入；材料不足/互相矛盾的题目记录排除原因。
- 宁可漏连，不制造错连；证据不足的题对保留候选，不强行写入。
- 每次请求原始返回落盘；费用按 usage token 记录（免费端点 `cost: "0"` 也照记）。
- 写入必须记录 `writes.jsonl`（`{batch_id, dir, item, action, hash_before}`），
  撤销只删除本批新增项并校验冲突，不用旧文件整体覆盖后续人工编辑。
