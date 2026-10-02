# 批次 pre-full-20261003 工作记录

批次：全仓 pre 关系补齐（长期任务）
依据：`docs/plans/pre-relations-full-coverage-plan.md`（执行规格）、
`docs/plans/pre-relations-full-coverage-review.md`（独立审核）
模型：`small-sheep/deepseek-v4.1-flash`（主 agent 与全部 worker 统一）
提交授权：按专题 commit（不 push）

## M0a（已完成，前一批交付）

难度单源（`tag-config.json` ↔ `lib/problem.js` 启动校验）、候选不占写入名额、
候选窗口 `1 ≤ Δrank ≤ 2`、辅助标签配置化。提交 `22e4e819`。

## M0b 离线实现（本阶段完成）

提交 `dd771e46`。

### 交付物

| 文件 | 作用 |
| --- | --- |
| `scripts/.../relation_batch/prebatch_lib.py` | 共享逻辑：难度校验、候选生成、专题切分、引文定位、关键词匹配、全局仲裁、frontmatter 关系编辑、环检测、预算器、状态目录 |
| `scripts/.../relation_batch/prebatch_ops.py` | 8 个子命令实现：`shard`/`prescreen`/`pilot`/`dispatch`/`collect`/`grounding`/`apply`/`ledger`/`recheck` |
| `scripts/.../relation_batch/prebatch_selftest.py` | fixture 仓库上的端到端离线自检（§15.1） |
| `scripts/.../relation_batch/questions-pre-v6.json` | v5 三问 + 新增可机检 `step_reused` |
| `scripts/.../relation_batch/worker-brief-template.md` | worker 任务书模板 |
| `scripts/.../relation_batch/worker-result.schema.json` | worker 结果 schema |
| `scripts/.../relation_batch/jev_client.py` | key 池（round-robin、429 切 key、401 剔除）、`JevAuthError` |

### 关键实现细节（自检捕获的真实缺陷）

1. **两个 hash 分工（§7.1-3）**：`hash` 用于写入前外部编辑检测；`evidence_hash`
   （正文 + 非关系 frontmatter，排除 `pre`/`common`/`recommend`/`updated`）作为判断证据版本。
   否则本批自己写 `pre` 会让后续专题全部误判为 `stale-external`。
2. **`Ctx.refresh()`**：批次持续改 frontmatter，凡规划/机检前必须重新读盘。
   自检发现缓存导致 `edges` 过期 → 重复写边。
3. **跨专题替换（§6.1-3）**：池中含本批已写边；被更强候选挤出时定点删除并记 `replace-pre`。
   自检发现原实现无法删除本批自己写过的较弱关系。
4. **空结果占位不预建**：缺失即「未返回」，不会被误判成有效结果。
5. **recheck 口径（§12 约束 4）**：历史边的方向/Δrank 差异只记为 `legacy_window_violation`
   供独立审核，不自动删除。

### §15.1 检查结果

报告：`relation-batches/pre-full-20261003/m0-checks.json`（**9 项全部通过**，覆盖规格 6 项关键项）

| # | 检查 | 结果 |
| --- | --- | --- |
| 1 | 难度单源：漂移即拒绝 + 同难度不入管线 | ✅ 注入漂移后拒绝启动；候选 Δ∈{1,2} |
| 2 | 候选不占名额 + 全局去重恰好分配一次 + 子分片覆盖 | ✅ B1 有 10 个候选；分配 74/74；子分片并集=父集合且互斥 |
| 3 | dispatch 与任务书 | ✅ dry-run 不落盘；占位符全替换 |
| 4 | prescreen 模拟（零付费）+ 预算预留不越界 | ✅ 阈值可校准 |
| 5 | worker schema 与证据 | ✅ 引文不可定位/模板句/行号越界/方向颠倒/身份缺失/字段残缺 全部不升级 |
| 6 | 四键仲裁 | ✅ 顺序无关；超限记 deferred；历史占位保留 |
| 7 | 恢复与预算 | ✅ 旧 attempt 不覆盖；幂等；正文不变；台账可定点撤销；外部编辑不覆盖 |
| 8 | 闸门与抽检 | ✅ M1 完成阻止写入；审核发现问题阻止写入；recheck 不误判 |
| 9 | 跨专题 replace-pre（§6.1-3） | ✅ 弱边被替换并记台账 |

### 全仓分片结果（真实仓库，零付费）

```
题目 2169（有难度 1762）
候选对 50480（+39 条已有 pre 被排除）   ← 规格 §2 记载 50519
分片 258（topic 169 / subtopic 84 / remainder 5）
固定归属校验：分配 50480/50480，重复 0，未分配 0
产量数学上界：(1762 − 459) × 3 = 3909
```

最大专题（按候选对数）：动态规划 11284、字符串 10275、贪心 6858、数学 6358、枚举 5948。

## M1 有界试点（进行中）

- 选点：最大专题 **动态规划**，≤200 个候选（覆盖 12 个分片），兼顾子类与剩余分片。
  清单：`m1-candidates.txt`
- 后续：Jev 初筛 → worker 严格裁定 → 接地机检 → `accept` 全查 → 申请 `--review-file` → `apply`
- 完成后必须暂停：交付 `canary-report.md` 并通知派发器，等用户确认后才进 M2。
