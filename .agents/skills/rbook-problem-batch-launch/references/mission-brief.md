# 批次任务书模板

`rbook-problem-batch-launch` 的任务书模板。编队和模型分配规则见 [SKILL.md](../SKILL.md)。模板里 `<>` 处替换实际内容，未指定的项按 SKILL.md 默认值。

## 主 agent 任务书

```text
你是本次批次的主 agent，负责在本 herdr workspace 里编排完成一批 rbook 题目工作。
仓库：<仓库绝对路径>
批次：<批次名，如 p11230-batch>

## 任务清单
| 题目 | 任务类型 | 分配模型 | 理由 |
| --- | --- | --- | --- |
| luogu/P11230 | 编写 | <model-id> | <理由> |
| luogu/P11231 | 优化 | <model-id> | <理由> |

## 编队要求
- 每道题一个子 agent，每个 agent 独占一个 tab：herdr tab create 建 tab，
  从响应读 .result.tab 和 .result.root_pane，在根 pane 用 herdr agent start
  启动 pi（名称如 <批次>-sub-p11230，--model 用上表模型）。
- 一道题只有一个写手，子 agent 之间不共写同一题目目录。
- 用 herdr agent prompt --wait 派活、agent read 查状态；子 agent 卡住时读状态分析，转达用户而不是代答。

## 子任务要求（每题发给子 agent）
- 按 AGENTS.md 工作流：先读 README.md 第 6 节和 CONTEXT.md，用对应本地 skill
  （oj-problem-analysis-writer / oj-problem-analysis-reviewer / rainboy-brain 等）。
- 任务类型「编写」：从零产出 problems/<oj>/<id>/index.md 题解、代码、样例素材。
- 任务类型「优化」：改进现有 index.md（证明、结构、代码一致性），保留正确内容。
- 代码遵守 oj-cpp-competitive-style；Markdown 遵守 rbook-markdown + oj-problem-format-spec。
- 修改验证：编译 -Wall -Wextra、样例、需要时 gen.py 对拍（300-500 组）、
  完成后 npm run check:content。
- 题目目录下任何被跟踪文件变动，都要把 index.md frontmatter 的 updated
  刷成当前时间，否则 pre-push 会拦截。
- 默认不 commit，改完列文件清单等用户验收；若批次指令授权 commit：
  按题一个 commit，conventional commit，中文描述。

## 验收要求
<默认：编译无警告、样例通过、对拍通过、npm run check:content 通过>

## 汇报格式
批次完成后给我（主 agent）一份汇总，包含：
每题的改动文件、验证结果、遗留问题、建议的 commit message（若授权 commit），
以及没有完成的项和原因。我会汇总后转达用户。
```

## 子 agent 任务书

```text
你是 <批次名> 批次里负责 luogu/P11230 的子 agent。
仓库：<仓库绝对路径>
任务类型：编写 | 优化（按分配）

## 做什么
<编写：从零产出题解；优化：改进现有题解的具体目标，如"证明重排精简"、"代码去 edge 存储"。>

## 硬约束
- 先读 <仓库>/AGENTS.md、README.md 第 6 节、CONTEXT.md，再用对应本地 skill。
- C++ 代码遵守 oj-cpp-competitive-style；Markdown 遵守 rbook-markdown 与
  oj-problem-format-spec；@include-code 引代码，引用代码、图片和原题来源一致。
- 修改前验证（编译 -Wall -Wextra、样例、对拍 gen.py 300-500 组），
  完成后跑 npm run check:content。
- 本目录任何被跟踪文件变动，刷新 index.md frontmatter 的 updated 为当前时间。
- 默认不 commit；<若授权：按题一个 commit，conventional commit 中文描述>。

## 汇报格式
改动文件清单、验证结果（编译/样例/对拍/检查命令）、遗留问题、
建议 commit message。只改自己这道题的目录。
```

## 指令解析例子

用户指令：

> 写 P11230 和 P11231，优化 P11229，模型用 gemini-3.5-flash 到 gpt-5.5

解析结果（缺口用 grill-me 问清后补上）：

```text
题目清单：
- luogu/P11230 编写
- luogu/P11231 编写
- luogu/P11229 优化
模型范围：gemini-3.5-flash / kimi-k2.6 / gpt-5.5
主 agent 模型：默认（派发器同模型）
验收：默认；commit：默认不提交
```
