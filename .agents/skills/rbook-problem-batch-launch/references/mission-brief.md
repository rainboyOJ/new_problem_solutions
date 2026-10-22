# 批次任务书模板

派发器填好主任务书；主 agent 每次派题填好子任务书。尖括号必须替换为实际值；协议和 skill 使用绝对路径，使独立 pi 无需继承派发器上下文。

## 主 agent 任务书

```text
你是本批次主 agent，负责派题、监督、指导、独立验收和回收 worker。
仓库：<repo-path>
批次：<batch>
唯一 workspace：<workspace-id>
主 tab/pane：<main-tab-id> / <main-pane-id>
并发上限：<默认 3 或用户指定的正整数>
允许的模型：<准确 model id 清单>
提交授权：<默认不 commit、不 push；或用户明确授权的范围>

先读：
- <repo-path>/AGENTS.md、README.md 第 6 节、problems/CONTEXT.md。
- <repo-path>/.agents/skills/rbook-problem-batch-launch/SKILL.md。
- <repo-path>/.agents/skills/rbook-problem-batch-launch/references/supervision.md。
- <repo-path>/.agents/skills/rbook-problem-batch-launch/references/mission-brief.md 的子任务模板。

题目清单（内部标识必须带 oj）：
<oj/id | 编写或优化及目标 | 分配模型 | 分配理由，逐题列出>
附加验收要求：<用户要求；未追加则使用 skill 默认标准>

执行约束：
- 只使用上面的 workspace，根 tab 运行你自己，创建 min(并发上限, 题数) 个 worker tab 并循环复用。
- 批次只有主、子两层。子 agent 每次只做一道题，均用 pi --no-session --no-extensions 启动（不加载任何扩展），不得创建下级 agent。
- 用独立 pi 做下一题；不能在旧上下文直接追加下一题，也不能不断新建 tab。
- worker tab 名用当前题目 <oj>-<pid>（如 luogu-P5657）；复用 tab 派下一题时用 herdr tab rename 改成新题。
- 按监督协议维护本地批次状态、分配代次、活动时间、错误时间、重启计数和验收证据。
- 每 3 分钟巡检所有活动槽位；派题不加长时间 --wait。验收和测试也不能阻塞其他槽位巡检。
- 连续 5 分钟无有效进展时介入；动画/计时/重复重试不算进展。401 立即介入，503 从首次连续失败最多等 5 分钟，命令一直不返回也要处理。
- 先读现场并用 Esc 打断；恢复后可以发信息指导继续。无法恢复时确认旧 pi 和遗留任务退出，再原 tab 重启并接续文件；每题整个批次最多自动重启 2 次。
- DONE <题号> 是提交验收。读取实际文件和测试证据，使用 reviewer 独立审查；不通过发具体问题给原子 agent 修改，修改后重新 DONE。
- 验收通过才结束旧 pi，确认 shell 空闲后将原 tab 派给下一题。异常题按协议记录，清理其进程后可释放槽位；无法确认清理则隔离槽位。
- 每题按 oj-problem-workflow 执行或恢复；真实子任务有分析与取舍，有教学价值的独立解法按计划讲解和验证。给每个子 agent 完整传递单题要求和 skill 绝对路径。
- 所有题目都有结论后统一执行 npm run check:content，最终逐题汇报通过/异常、文件、教学覆盖、验证、重启次数和遗留问题。
- 默认不提交；有授权也由你验收后按题提交，只暂存该题文件，不操作其他工作者的改动。
```

## 子 agent 任务书

```text
你是 <batch> 批次做题子 agent，只负责 <oj/id>。
仓库：<repo-path>
题目目录：<repo-path>/problems/<oj>/<id>
任务：<编写或优化，以及具体目标>
本次分配代次：<assignment-id>
完成标记：DONE <id>
附加要求：<用户要求，或无>
恢复/返修上下文：<首次任务写“首次”；否则给出现场摘要、已改文件、验证情况和待修问题>

开始：
1. 读取仓库 AGENTS.md、README.md 第 6 节、problems/CONTEXT.md。
2. 读取 <repo-path>/.agents/skills/oj-problem-workflow/SKILL.md 及其 references/stages.md，按实际材料恢复单题阶段。
3. 按当前阶段读取 planner、对应代码风格、oj-judge-and-stress、writer、format 和 reviewer，不一次加载所有无关 references。
   本轮已经由 workflow 协调；专项 skill 返回产物和问题，不反向重启 workflow。
   题面缺失才获取，不加默认覆盖参数，保留已有正确内容与用户笔记。

交付要求：
- 只修改自己题目的目录，不创建任何下级 agent，不修改共享配置或其他题，不 commit、不 push。
- 真实子任务都记录分析与教学取舍；递进、分支、替代或合并按 planner 的真实关系组织。选中算法提供所需代码，只在适用限制内测试部分分程序。
- 有独立教学价值的完整解法按规划分别讲解、提供代码并验证；分档和多解法可以同时存在。默认主解 main.cpp，其他目标语言用相应 main.<ext>；其他算法独立命名并引用。
- 用过程文档记录推导和证据，正式题解写入 index.md。引用代码、图示、题面来源保持一致。
- 对实际 C++ 文件使用 C++17、-Wall -Wextra 编译并消除错误和警告；验证满分解法的原题样例及边界。
- 验证统一使用 oj-judge-and-stress；本批次适用时用可靠小数据基线对拍 300–500 组，记录实际命令、规模、结果和失败原因；替代解法及子任务代码分别验证。无法执行的项如实写明，不能虚报通过。
- 运行 check_problem.py 和 check_relations.py；check_analysis_quality.py 存在时按 reviewer 要求使用。
- 刷新 index.md frontmatter 的 updated 为当前时间，保留原 date。全库 npm run check:content 由主 agent 在收尾时统一运行。
- 外部命令设置合理超时，长测试拆分执行并保留可检查的结果。遇到题面缺失、认证错误或无法推进，立即报告主 agent；不要输出虚假的心跳刷屏。

交付协议：
- 将交付报告保存到题目目录的 problem-analysis-workspace/batch-handoff.md，写明批次、分配代次、题号、改动文件、当前 workflow 阶段、分档/多解法覆盖、验证命令与结果、未完成项和下一步。
- 在回复中报告要点，最后单独一行输出上面指定的完成标记（例如 DONE P11230），不要加 Markdown 装饰。DONE 仅表示请求验收。
- 输出 DONE 后保持 pi 可交互，停止修改，等待主 agent。验收不通过按具体意见返修，更新报告后再次输出相同完成标记。
- 不提前自行退出，不自行接下一题。只有主 agent 验收通过并回收后，原 tab 才用于下一题。
```
