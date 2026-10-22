# 过程文档与草稿

## 目录

```text
problems/<oj>/<problem_id>/
  problem.md
  index.md
  main.cpp / main.<ext>
  brute.cpp                 # 算法题按需
  gen.py                    # 随机验证按需
  problem-analysis-workspace/
    01-problem-understanding.md
    02-observation-and-model.md
    03-solution-derivation.md
    04-correctness-and-edge-cases.md
    05-complexity-and-implementation.md
    06-final-index-draft.md
    duipai-report.md        # 实际对拍后才生成
    final-visualization.md  # 需要末尾图示时才生成
    viz_render.py           # 使用可视化 skill 时才生成
```

核心阶段文件可以合并，但不能丢失关键信息。脚手架已有的空文件可以保留，但不能把文件存在当作阶段完成；合并后在交付报告指出实际记录位置。专项文件只在确实需要时维护。

## 材料阅读与核验

先核实题面和完整约束，再复用已有过程文档、代码及文章。题意、约束和子任务以核实的原题为准；代码用于核对实际实现，不能反过来定义题目约束；文章格式以格式 skill 为准。来源之间矛盾时记录并核查，不靠猜测补齐。

整体阶段由 [`oj-problem-workflow`](../../oj-problem-workflow/SKILL.md) 协调。`01` 至 `05` 的算法材料由 [`oj-solution-planner`](../../oj-solution-planner/SKILL.md) 阶段建立，执行实现和验证的 agent 补充实际证据。字段和状态统一见 [`handoff.md`](../../oj-solution-planner/references/handoff.md)。writer 复核并消费这些材料，负责文章结构确认、可视化评估和 `06` 草稿；无需为各阶段另建一套文件。

## 阶段文件

`01-problem-understanding.md`：精确描述题意，不急着讲算法。

```markdown
# 题意理解
## 输入与输出
## 要求求什么
## 约束条件
## 等价表述
```

`02-observation-and-model.md`：记录直接想法、关键性质、模型、候选解法及关系。候选和 `文章结构判定` 按 planner 的交接约定填写，writer 确认正式布局，算法或实现有变化时复核。已有有效字段无需为了改名而重写。写作阶段补充可视化评估，说明是否需要、推荐形式、解释对象和不使用的原因。

```markdown
# 关键观察与模型
## 直接想法
## 关键性质
## 可用模型
## 为什么这个模型适用
## 文章结构判定
## 可视化评估
```

`03-solution-derivation.md`：按已选解法关系解释推导。递进型说明复用的观察、消除的瓶颈或取消的假设；并列型分别推导各解法并比较取舍；直解题说明为何没有独立暴力；语言学习题改为说明语法概念与代码的映射。以下仅是暴力到正解的示意，其他布局按需调整标题。

```markdown
# 解法推导
## 朴素想法
## 瓶颈分析
## 优化思路
## 最终做法
## 与代码实现的对应关系
```

`04-correctness-and-edge-cases.md`：写正确性理由、反例检查、边界和验证记录。多解法逐个记录适用约束、实际执行的检查及结果；子任务实现不以满范围测试作为通过要求，也不能把小范围通过写成全范围通过。算法题说明 `brute.cpp` 是否足以对拍；语言学习题记录样例/手工运行和语法边界。

```markdown
# 正确性与边界情况
## 正确性说明
## 可能的反例检查
## 边界情况
## 对拍或手工验证记录
```

`05-complexity-and-implementation.md`：只解释关键实现对应关系，不逐行翻译代码；算法题同时比较优化实现和暴力，语言学习题说明语法在最终代码中的位置。

```markdown
# 复杂度与实现
## 时间复杂度
## 空间复杂度
## 关键变量
## 核心循环
## 边界处理
## 与最终代码的对应关系
```

`06-final-index-draft.md`：先写最终草稿，再回写 `index.md`。草稿必须采用已记录的四种布局之一，包含每个正式解法的 `### 代码` 和正式主解的 `@include-code(./main.<ext>, <lang>)`。frontmatter 必须有非空 `description`、复核后的 `difficulty` 和准确标签，不要留下 `tags: []`，除非材料确实不足。

## 写作顺序

由 workflow 完成或复核规划、实现与验证后，writer 消费材料并确认正文布局；输入缺口返回协调者处理。递进层写清适用范围、复杂度、瓶颈或限制性假设，说明下一层如何推进；并列解法各自说明核心观察和取舍。正解写思路、正确性、复杂度及代码对应。正文比过程文档短，不能复制整个工作区。

完成时核对 `文章结构判定` 是否有具体内容、最终布局是否与正文一致、每份引用代码是否实现对应做法。空字段、备选值、仅有标题或 HTML 占位注释均不算阶段完成；未验证项如实记录。过程文件保持本地忽略，不作为共享 CI 的必需输入。

frontmatter 字段、四种布局、公式和代码嵌入以 `../oj-problem-format-spec/references/` 为准。难度优先读取洛谷官方字段：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py luogu <problem_id> --json
```

洛谷 id `0..7` 对应 `未知`、`入门`、`普及-`、`普及`、`普及+/提高-`、`提高`、`提高+/省选-`、`省选/NOI-`；不能可靠取得时写 `未知`。
