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

核心阶段文件可以合并，但不能丢失关键信息。脚手架已有的空文件可以保留；专项文件只在确实需要时维护。

## 信息来源优先级

1. `problem-analysis-workspace/*.md` 中用户已写材料
2. 正式代码 `main.*`
3. 算法题的 `brute.cpp` 和其他解法代码
4. 现有 `index.md`
5. 用户提供的题面或来源 URL
6. `oj-problem-format-spec` 的格式规则

已有过程文档和正文必须先读，保留有价值内容；来源之间矛盾时记录不确定性，不靠猜测补齐。

## 阶段文件

`01-problem-understanding.md`：精确描述题意，不急着讲算法。

```markdown
# 题意理解
## 输入与输出
## 要求求什么
## 约束条件
## 等价表述
```

`02-observation-and-model.md`：记录直接想法、关键性质、模型、适用理由，并包含布局判定。还要记录可视化评估，至少说明是否需要、推荐形式、解释对象和不使用的原因。

```markdown
# 关键观察与模型
## 文章结构判定
## 直接想法
## 关键性质
## 可用模型
## 为什么这个模型适用
## 可视化评估
```

`03-solution-derivation.md`：按解法层次解释从朴素到最终的推导；直解题说明为何没有独立暴力；语言学习题改为说明语法概念与代码的映射。

```markdown
# 解法推导
## 朴素想法
## 瓶颈分析
## 优化思路
## 最终做法
## 与代码实现的对应关系
```

`04-correctness-and-edge-cases.md`：写正确性理由、反例检查、边界和验证记录。算法题说明 `brute.cpp` 是否足以对拍；语言学习题记录样例/手工运行和语法边界。

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

先形式化题意，再写关键观察和解法关系；暴力/子任务层写清适用范围、复杂度和瓶颈，下一层必须从瓶颈推出；正解写思路、正确性、复杂度及代码对应。正文比过程文档短，不能复制整个工作区。

frontmatter 字段、四种布局、公式和代码嵌入以 `../oj-problem-format-spec/references/` 为准。难度优先读取洛谷官方字段：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py luogu <problem_id> --json
```

洛谷 id `0..7` 对应 `未知`、`入门`、`普及-`、`普及`、`普及+/提高-`、`提高`、`提高+/省选-`、`省选/NOI-`；不能可靠取得时写 `未知`。
