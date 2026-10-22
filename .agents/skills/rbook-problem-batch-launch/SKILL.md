---
name: rbook-problem-batch-launch
description: >-
  Launch and supervise a batch of rbook OJ analyses in one Herdr workspace
  with one main pi agent and reusable worker tabs. Use for 批量写题、批量优化题目、
  批量写题解、启动批次、Herdr 题目任务编排 and assigning models to problem workers.
  Supports bounded concurrency, stalled-worker recovery, review before tab reuse,
  progressive subtasks and multiple solutions. The dispatcher delegates problem work.
---

# rbook 批量题目工作区派发

派发器解析批次指令，创建一个批次 workspace，把任务书交给主 agent；主 agent 在其中派题、监督、指导、验收和回收。单题执行由做题子 agent 按 `oj-problem-workflow` 完成；本 skill 只协调批次、监督与独立验收，不另维护单题步骤。

## 编队约定

- 一个批次只有一个 workspace：主 agent 独占根 tab，另有固定数量的 worker tab。恢复已有批次时复用记录的 workspace，不另建一个。
- 默认并发数为 3，启动时可指定正整数；worker 数量为并发数与题目数量的较小值。20 道题、并发 3 时共 4 个 tab，不为 20 道题各建 tab。
- 批次内部只有主 agent → 做题子 agent 两层；子 agent 不得再创建下级 agent。
- 每个子 agent 只负责一道题，所有做题子 agent 使用 `pi --no-session --no-extensions`（不加载任何扩展）。同一道题始终只有一个写手。
- worker tab 的名字用当前题目的 `<oj>-<pid>`（如 `luogu-P5657`）；tab 复用派下一题时用 `herdr tab rename` 改名，让 tab 名始终指向正在做的题。
- 子 agent 输出 `DONE <题号>` 仅表示提交验收。主 agent 验收通过后结束旧 pi，确认原 pane 回到空闲 shell，再在原 tab 启动全新的 pi 做下一题。
- 主 agent 可以发消息指导、纠偏和要求返修，包括打断后恢复响应的子 agent。

## 前置检查与输入

先读取已安装的 Herdr skill，验证 `test "${HERDR_ENV:-}" = 1`；失败则说明无法在当前环境编排并停止。通过后用 `herdr --help` 及 `herdr workspace`、`herdr tab`、`herdr agent`、`herdr pane` 查看本机语法；`pi --help` 核实参数。不要用缺少参数的变更命令探测帮助。

| 要素 | 规则 |
| --- | --- |
| 题目清单 | 必须明确；裸题号默认 luogu，内部用 `oj/id` 去重和标识 |
| 任务类型 | 每题明确编写或优化，可混合；先核对已有题解状态 |
| 模型清单 | 使用用户允许的准确 model id，保留 `provider/id`；范围不明确就澄清，不自行补中间模型 |
| 主 agent 模型 | 优先用户指定，否则沿用派发器模型；无法映射为 pi 可用 id 时澄清 |
| 并发数 | 默认 3，用户可覆盖 |
| 验收 | 默认按本文和监督协议执行，可追加用户要求 |
| commit | 默认不 commit、不 push；若已授权，由主 agent 验收后按题提交，避免子 agent 并发操作 Git index |

只询问无法从环境和现有授权确定的事项；每次一个问题，附推荐答案并等待回答。已明确或已确认的规则不重复问。用户显式调用 grill-me 时遵循其逐项问答和最终共识确认要求。

启动前展示题目与模型分配、并发数、workspace 名和任务书摘要；当前会话已批准具体方案就直接执行，否则确认一次。优化目标不存在时说明情况，确认是否改为新建。

模型分配在允许清单内按题目需要选择：常规任务优先成本和速度，复杂证明、难题或正确性存疑的任务优先能力，并记录分配理由。用户已指定逐题模型时遵从指定。

## 启动

派发器填充 [任务书模板](references/mission-brief.md)。主 agent 必须读取 [监督、验收与回收协议](references/supervision.md)，据此运行完整批次。

以下尖括号均为待替换参数；通过结构化工具参数传任务书，使用 shell 时正确引用，长任务书可先写本地文件再安全读取传入。

1. 新批次只创建一次 workspace，保持用户焦点和仓库 cwd：

   ```bash
   herdr workspace create --cwd <repo-path> --label <batch> --no-focus
   ```

   从 JSON 读取 `.result.workspace`、`.result.tab`、`.result.root_pane` 的实际 ID，记录后续使用，不根据侧栏顺序或示例推导。

2. 在根 pane 启动主 agent；主 agent 保留会话，便于恢复监督：

   ```bash
   herdr agent start <batch>-main --kind pi --pane <root-pane-id> -- --model <main-model>
   herdr agent prompt <batch>-main "<已填充的主任务书>"
   ```

3. 主 agent 建立固定 worker 池；每个槽位只创建一次 tab，然后派一题：

   ```bash
   herdr tab create --workspace <batch-workspace-id> --cwd <repo-path> --label <oj>-<pid> --no-focus
   herdr agent start <worker-name> --kind pi --pane <returned-pane-id> -- --no-session --no-extensions --model <assigned-model>
   herdr agent prompt <worker-name> "<已填充的单题任务书>"
   ```

   tab 创建结果读取 `.result.tab`、`.result.root_pane`。tab 名即当前题目 `<oj>-<pid>`；槽位复用派下一题时执行 `herdr tab rename <tab-id> <oj>-<pid>` 更新为新题。agent 名包含批次、槽位和启动代次，满足 `[a-z][a-z0-9_-]{0,31}`，在当前 server 唯一。

4. 派发和指导不使用长时间 `agent prompt --wait`，避免串行派题或停止监督其他槽位。提交成功不代表已开工，下一轮巡检核实响应。启动超时、`agent_not_ready` 或 prompt stalled 时先读现场，不重复启动或重发。巡检同样不要写成一条长阻塞命令（自建 watch 脚本用长 `sleep` 循环加超时上限）：单次工具调用最多阻塞约 90 秒，然后回到自己的回合分段处理；完成标记读自 pane 渲染输出，匹配要容错（`grep -oE 'DONE +[0-9A-Za-z]+'`），不要行首锚定。
5. 派发器报告 workspace ID、主 agent 名、并发数、模型分配及进度查询方式。主 agent 持续监督，直到所有题目都有验收通过或异常结论。

## 单题任务与 skill 路由

子 agent 先读仓库 `AGENTS.md`、README 第 6 节和 `problems/CONTEXT.md`（题解建模词汇），再读取实际适用的 skill。以下路径相对仓库 `.agents/skills/`：

| 职责 | skill |
| --- | --- |
| 单题阶段协调与恢复 | `oj-problem-workflow/SKILL.md` |
| 解法规划、分档递进及多解法关系 | `oj-solution-planner/SKILL.md` |
| 正文写作 | `oj-problem-analysis-writer/SKILL.md` |
| 样例、边界、对拍与性能验证 | `oj-judge-and-stress/SKILL.md` |
| 优化前审查、子 agent 自查和主 agent 独立验收 | `oj-problem-analysis-reviewer/SKILL.md` |
| 文章布局、frontmatter、代码引用 | `oj-problem-format-spec/SKILL.md` 与 `rbook-markdown/SKILL.md` |
| C++17 代码 | `oj-cpp-style/SKILL.md` |
| 需要样例或算法图示 | `oj-sample-visualizer/SKILL.md` |
| 需要维护前置、类似、推荐关系 | `oj-problem-relation-writer/SKILL.md` |

需要加强“如何想到”的推理时再使用已安装的 `rainboy-brain`。没有触发的可视化或关系任务不机械追加。

### 单题执行与批次附加要求

worker 读取 [`oj-problem-workflow`](../oj-problem-workflow/SKILL.md)，从实际未完成的阶段接续，不在批次内再执行一套题面、规划、代码和写作流程。缺失题面才获取，已有材料保留；阶段失败按 workflow 返回，无法自行解决的阻碍报告主 agent。

批次任务书明确交付范围与额外验收要求：

- 官方子任务都要有分析结论；同算法覆盖的档位合并，有教学价值的分支与独立完整算法说明取舍，不按档数制造代码。
- 正式与部分分实现标明范围，各自在适用条件内验证；同一算法的多语言实现不冒充独立解法。
- 默认主解为 `main.cpp`，用户指定其他语言则用对应 `main.<ext>`；其他文件按算法命名和引用。
- worker 只修改分配题目的目录，不创建下级 agent，不操作共享 Git index；全库检查由主 agent 统一执行。
- 单题的 workflow 状态可并入 `batch-handoff.md`，不要仅为格式再维护重复状态。批次、分配代次、题号和当前验证证据必须可追溯。

本批次 `DONE` 仍只表示提交验收；workflow 的自查不能代替主 agent 的独立验收。

## 监督与收尾

监督协议规定每 3 分钟巡检、5 分钟无有效进展处理、401/503 分流、指导与最多两次自动重启、独立验收、旧进程退出及 tab 复用。主任务书必须附协议的绝对路径，不能只传“注意监督”一句话。

最终汇报每题状态、文件、分档与多解法覆盖、验证证据、重启次数和遗留问题；异常题不能计为完成。主 agent 在所有写手停止修改后统一运行 `npm run check:content`，记录本批问题与原有问题。全局检查失败不能声称批次全部通过。

已获提交授权时，主 agent 按题使用 conventional commit 和中文描述；仅暂存本题已验收变更，不能顺带提交原有或其他批次的改动。

只管理本批创建或明确交接的 agent 和 pane。不要关闭 tab 来回收 worker，不操作其他批次，不运行 `herdr server stop`、不杀 Herdr 主进程。审批或权限问题按已有授权处理，确实超出授权才转达用户；普通算法和返修问题由主 agent 指导解决。
