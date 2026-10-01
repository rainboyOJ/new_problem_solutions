---
name: rbook-problem-batch-launch
description: >-
  Launch Herdr workspaces that write or improve OJ problem analyses in this
  repository with one main pi agent plus per-problem subagents. Use this skill
  whenever the user wants to 批量写题, 批量优化题目, 批量写题解, 发布批次指令,
  启动一个 workspace 主 agent + subagent, 用 herdr 编排题目任务, 开一批 agent
  做题, assign models to problem workers, or says 启动批次/开新 workspace 做题.
  It parses the batch instruction (problems, model range, task kind), asks
  grill-me style questions when anything is unclear, confirms the launch plan,
  then creates the workspace and hands the main agent a mission brief. It does
  not solve problems itself.
---

# rbook 批量题目工作区派发

你是**派发器（dispatcher）**。用户在当前 herdr workspace 里给一条批次指令（哪些题目、model 的范围、写还是优化），你负责：

1. 解析指令，缺口用 grill-me 问答补齐。
2. 共识确认启动方案。
3. 新建一个 herdr workspace，启动主 agent，并把批次任务书交给它。
4. 主 agent 在自己的 workspace 里为每道题起一个子 agent（每个 agent 一个 tab），完成写题/优化。

题目本身由新 workspace 里的主 agent 和子 agent 完成；派发器不写题解、不改题目文件。

## 前置检查

所有 herdr 命令执行前先确认本 agent 在 herdr 里：

```bash
test "${HERDR_ENV:-}" = 1
```

检查失败就说明无法编排 herdr 工作区并停止。检查通过后，先看 `herdr --help` 和相关命令组帮助（`herdr workspace`、`herdr tab`、`herdr agent`），安装的二进制是命令语法的权威；从 JSON 响应读 ID，不要凭例子猜。

## 指令解析

一条批次指令应包含这些要素：

| 要素 | 必要性 | 说明 |
| --- | --- | --- |
| 题目清单 | 必须 | 明确题号，如 `P11230 P11231` 或 `luogu/P11230`；裸题号默认 luogu |
| 任务类型 | 必须 | 每题是「编写」（新建题解）还是「优化」（改进现有题解），可混合 |
| 模型清单/范围 | 必须 | 子 agent 可用的 model id 列表或范围 |
| 主 agent 模型 | 可选 | 默认与派发器同模型 |
| 验收要求 | 可选 | 默认：编译警告、样例、对拍、`npm run check:content` |
| commit 授权 | 可选 | 默认不 commit，改动留给用户验收；指令明确授权才让主 agent 按题 commit |

解析后核对题目现状：「优化」的题必须已有 `problems/<oj>/<id>/index.md`，不存在就在 grill 里指出；「编写」的题目录可以不存在，但要确认题目来源（原题 URL/题面）已有着落。

## grill-me 问询

指令缺任何"必须"要素、题目指认含糊（如"那几道 DP 题"）、"写还是优化"不明、模型清单没给，都**不要猜**——用 `ask_user` 交互表单把缺口问全：

- 每问带推荐答案（`recommendation`），让用户确认或改一句话就能发车。
- 一轮问全所有缺口，全部达成共识后才进入启动；中途用户改主意就按新共识更新解析结果。
- 用户指令里已写清的项不再重复问。
- 题目数量大时，把解析出的「题目 → 任务类型」对照表给用户过目确认。

## 启动共识

动手前把启动方案展示给用户，等确认（推荐答案"确认启动"）：

- 新 workspace 名称（按批次起，如 `p11230-batch`）。
- tab 布局：主 agent 1 个 tab + 每题 1 个子 agent tab。
- 模型分配表：每题分到的 model + 理由（分配原则见下）。
- 任务书摘要：验收要求、commit 授权、汇报方式。

## 启动编队

确认后执行（命令语法以本机 `herdr` 帮助为准）：

1. 创建 workspace：

   ```bash
   herdr workspace create
   ```

   从响应读 `.result.workspace`、`.result.tab`、`.result.root_pane`。

2. 在 workspace 的根 tab 启动主 agent（名称带批次前缀，`[a-z][a-z0-9_-]{0,31}` 且全局唯一）：

   ```bash
   herdr agent start <batch>-main --kind pi --pane <root-pane-id> -- --model <main-model>
   ```

   `agent start` 返回即代表 agent 可交互；若返回 `agent_not_ready` 或 blocked，用 `herdr agent get` / `agent read` 看状态再决定，别重复启动。

3. 把批次任务书交给主 agent（模板见 [`references/mission-brief.md`](references/mission-brief.md)）：

   ```bash
   herdr agent prompt <batch>-main "<任务书>" 
   ```

   发出即可，不带 `--wait`（批次工作会跑很久）；`agent prompt` 只保证提交成功，不代表开始干活，必要时用 `herdr agent read` 确认它动起来了。

4. 向用户报告 workspace id、主 agent 名、模型分配表，并给出进度查询命令。

### 子 agent 编队规则（写进任务书）

- 主 agent 在自己的 workspace 里为每道题建一个 tab（`herdr tab create`，从响应读 `.result.tab` 和 `.result.root_pane`），在 tab 里起子 agent：

  ```bash
  herdr agent start <batch>-sub-p11230 --kind pi --pane <tab-root-pane-id> -- --model <assigned-model>
  ```

- 一个 tab 只放一个 agent；子 agent 之间不共写同一题目目录，一道题只有一个写手。
- 子 agent 的任务书用 [`references/mission-brief.md`](references/mission-brief.md) 里的子任务模板：题目、任务类型、模型、硬约束、验收、汇报格式。
- 主 agent 用 `herdr agent prompt --wait` 派活和收结果，用 `agent read` 查看卡住的子 agent；子 agent blocked（问询/审批）时把问题转达用户，不代答。

## 模型分配原则

用户给模型清单或范围，主 agent 在范围内自主分配：

- model id 原样传给 `pi --model`（保留 `provider/id` 形式，不改写、不用清单外的模型）。
- 常规编写（题意清晰、有样例和参考代码）：选清单里便宜/快的模型。
- 优化证明、重排推理、审稿、难题、正确性存疑：选清单里强模型。
- 同批混编时强弱搭配并在任务书里写明每题的理由，方便用户事后调整。

## 监督与收尾

- 查进度：`herdr agent list`、`herdr agent get <name>`、`herdr agent read <name> --source recent-unwrapped --lines 120`。
- 主 agent blocked 或超时无响应：先 `agent get` + `agent read` 看状态再决定下一步；超时不代表任务书没送达，不要盲目重发。
- 批次完成的标准：主 agent 报告每题完成情况（改动文件、验证结果、遗留问题）。
- 默认不自动 commit / push；用户验收后自己发 commit 指令，或按批次指令的授权让主 agent 按题提交（conventional commit，中文描述）。

## 安全规则

- `HERDR_ENV` 检查失败就停止，不要从 herdr 外部控制会话。
- 不关闭、不重启自己没创建的 workspace / tab / pane / agent；`workspace close --group` 绝不顺手加。
- 所有 ID 从 JSON 响应解析；agent 命名小写、全局唯一（用批次前缀防撞名）。
- blocked 的审批/问询一律转达用户，替 agent 做决定前必须征得同意。
- 需要 `--trust-repository` 时先向用户确认；不跑 `herdr server stop`，不杀 herdr 主进程。
