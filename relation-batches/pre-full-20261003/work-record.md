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

## M1 有界试点（已完成，暂停等用户确认）

提交：`59e852de`（初筛）、`6dd63012`（写入 18 条，专题 动态规划）。

选点：最大专题 **动态规划**，200 个候选 / 12 个分片。清单 `m1-candidates.txt`。

| 阶段 | 结果 |
| --- | --- |
| Jev 初筛 | 200 → 通过 19（9.5%），0 失败 |
| worker 裁定 | 19 单元 → accept 18 / doubtful 1，0 重启 |
| 接地机检 | 18 保持 accept，1 降级（`src_a_matches_quote`） |
| 写入 | 新增 18 / 替换 0 / 删除 0 / 延后 0 / 冲突 0 / stale 0 |
| 最终新增率 | 9.0%（分母=候选对） |

验收：拟写入 18 条 **全查**（机检全量 + 主 agent 逐条读原文），`errors_found=0`。
详见 `canary-report.md`、`m1-review.json`。

费用：Jev 上界记账 $0.0379，worker $0，10 key 全存活，未触发 $45 暂停线。

**闸门已锁定**：`state.json.gate.m1_complete = true`，`apply` 无 `--allow-after-gate` 时
报「M1 试点已完成但未获用户确认」（已实测）。等用户确认后再进 M2。

## 待用户裁定（canary-report §4/§7）

1. 是否进入 M2（动态规划剩余 11,084 对 → 字符串 8,857 对，上界约 $3.8 / 约 16 小时）
2. `coin-change→P1450` 这类「A 的步骤保留 + B 叠加新机制」是否判为合格（现按 §4② 先例判接受）
3. M2 是否启用独立审核 tab（本批未启用，为主 agent 自审）

## M2 扩展大专题 · 动态规划（已完成）

用户 2026-10-03 04:00 确认后进入 M2（`gate resume`）。M2 期间同时完成了全仓初筛。

### 全仓初筛（副产物）

`prescreen --parents` 的过滤器未生效（`cmd_prescreen` 漏传参数），实际把**全批 50,480 对**都跑了：

| 项 | 数值 |
| --- | --- |
| 候选对 | 50,480（完成率 100%） |
| 初筛通过 | **928**（1.84%） |
| 拒绝 | 49,552 |
| 失败 | 0 |
| 费用 | 上界记账 **$8.0547**（实际估计约 $6.2），10 key 全存活 |

**影响**：这不只是浪费——它把 M3/M4 所需的初筛一次做完了，M3 可直接进入 worker 层，
且证实规格原估 $5.1 偏乐观（实测上界 $8.05，仍在 $45 内）。
**教训**：`--parents` 传参漏接是静默失败，没有任何报错；工具改动后必须用 dry-run 验证过滤生效。

### 动态规划专题

| 阶段 | 数值 |
| --- | --- |
| DP 候选对（全专题） | 11,284 |
| 初筛通过 | 269 |
| worker 判定完成 | **269 / 269（100%）** |
| accept | 262 |
| reject（worker） | 4 |
| doubtful | 5 |
| 机检后 accept | 261 |
| **写入新增** | **150** |
| **替换 `replace-pre`** | **9** |
| 延后 `deferred`（超限） | 89 |
| 冲突 / stale | 0 / 0 |
| 错误（未取得有效裁定） | 0 |

写入后全仓 `pre` 边 **121 → 262**。

### 抽检（§8.2）

- 公式 `min(N, max(30, ceil(0.1N)))`：N=262 → **k=30**，固定种子 20261003 落盘 `m2-sample.json`
- 分层：模板级/非 high 优先抽一半，其余从 strong+high 抽
- **发现 1 处错误（样本错误率 3.3%，< 10% 阈值）**：
  `luogu/U661986 -> luogu/P1977` 的「复用」实为通用 DP 原则（最优子结构），
  §0 明确排除 → 已降级为 `reject`（`no-reuse`）并移出写入集合
- 另做**全量模式扫描**（找「只含通用框架词、无具体技术词」的 accept）：命中 3 条，
  复核后 2 条确为具体复用（`P1879→P8756` 状态压缩、`U661986→P2725` 容量维转移）保留，
  其中 `U661986→P2725` 强度由 `strong` 降为 `template-level`
- 处置符合 §8.4：错误已暂停写入、修正并分析同类规则；处置后 `errors_found=0` 才放行

### 本阶段修复的工具缺陷

| # | 缺陷 | 后果 | 处置 |
| --- | --- | --- | --- |
| 1 | `prescreen --parents` 参数漏传 | 静默跑了全批（$8.05） | 补齐传参并在 `apply --shard` 同样支持主标签 |
| 2 | 驱动脚本 `--cadence 15` 太短 | **122 个任务被派发后 worker 被过早杀掉** | 改为轮询「是否仍在 working」而非固定 sleep |
| 3 | 等待循环用 `state.json` 的 agent 名判活 | 名字滞后 → 误判空闲、提前杀 worker | 改用 `herdr agent list` 的实时 pane→agent 映射 |
| 4 | 重派发按 `status != 待派发` 去重 | worker 被杀后题对**永久卡住** | 改为「待派发任务可复用，不新建重复任务」 |
| 5 | 无重试上限 | 2 个 key 无限重派循环 | 加 `MAX_TASK_ATTEMPTS=3`（对齐 §7 最多 2 次重启） |
| 6 | 引文长度按纯字符数判（≤20） | 一行代码引文被误判非法，**43 条合格裁定丢失** | 改为折算权重（中文字数 + ASCII/4 ≤ 24），并同步任务书 |
| 7 | `grounding` 对已生效边重跑去重检查 | 每轮把已写关系重新判成 doubtful | 已生效边直接沿用原裁定（`already_applied`） |
| 8 | 闸门条件写成 `m1_complete` | 用户确认后仍永久阻断 M2 | 改为只拦 `waiting_user` |
| 9 | `apply --shard` 只接受单个分片 ID | 传列表时**静默写入 0 条** | 支持逗号分隔 ID 或主标签，未匹配时报错而非静默 |

新增 `prebatch_worker_pool.py`：把「回收 → 补位 → 启动 → 派题」的机械步骤集中成可复核脚本，
状态更新只走 `pre_batch.py` 的 dispatch/collect/grounding。M1 期间的手写 shell 循环正是缺陷 2–5 的来源。

## 后续里程碑

- M2–M3：大专题子类 → 其余专题（含独立审核）
- M4：历史 103 条 `recheck` 重审（`legacy-recheck.md`）
- M5：全仓交付报告
