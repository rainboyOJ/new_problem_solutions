---
name: local-python-learn-oj
description: >-
  用 Python 解 OJ 题目并学习 Pythonic 编程模式，同时生成完整的题解文章。
  这个 skill 编排 python-oj-learn（解题+教学）和 oj-problem-analysis-writer（写文章）两个 skill。
  当用户想用 Python 做 OJ 题、学习 Python 模式、用 Python 写题解文章时触发。
  触发词：Python 解题、Python 学 OJ、用 Python 做这道题、Python 题解、学 Python 模式。
  不要用于明确要求 C++ 解题的场景。
---

# Local Python Learn OJ

用 Python 解 OJ 题，学习 Pythonic 模式，并生成符合仓库规范的题解文章。

这个 skill 是一个**编排器**，分两个阶段调用已有 skill：

1. **解题阶段**：调用 `python-oj-learn` 完成 Python 解题和教学
2. **文章阶段**：调用 `oj-problem-analysis-writer` 写题解文章，但适配 Python 文件

## 前置条件

- `python-oj-learn` skill 已安装（`~/.agents/skills/python-oj-learn`）
- `oj-problem-analysis-writer` skill 已安装（`.agents/skills/oj-problem-analysis-writer`）
- `oj-problem-format-spec` skill 已安装（`.agents/skills/oj-problem-format-spec`）

## 目录结构

与标准题解目录一致，但代码文件使用 Python：

```text
problems/<oj>/<problem_id>/
  index.md
  main.py                    # Python 正解（替代 main.cpp）
  brute.py                   # Python 暴力解（可选，替代 brute.cpp）
  problem-analysis-workspace/
    01-problem-understanding.md
    02-observation-and-model.md
    03-solution-derivation.md
    04-correctness-and-edge-cases.md
    05-complexity-and-implementation.md
    06-final-index-draft.md
    07-ai-image-evaluation.md
```

## 阶段一：解题（调用 python-oj-learn）

加载 `python-oj-learn` skill，按其完整工作流执行：

1. 读题面、输入输出、约束、样例
2. 检索本地 Python 笔记（`PYTHON_OJ_NOTES_ROOT` 或默认路径）
3. 选择算法，写 Python 正解
4. 验证样例
5. 输出教学内容（题意、算法思路、Python 知识映射、模仿清单等）

阶段一产出：
- `main.py`：完整可提交的 Python 解法
- `brute.py`（可选）：Python 暴力解，用于对拍和教学
- 教学内容：算法思路、Pythonic 模式、C++→Python 对照、模仿清单

## 阶段二：写文章（调用 oj-problem-analysis-writer）

加载 `oj-problem-analysis-writer` skill，按以下 Python 适配规则执行。

### Python 适配规则

以下规则覆盖 `oj-problem-analysis-writer` 中的 C++ 默认行为：

#### 文件替换

| 标准（C++） | Python 适配 |
|---|---|
| `main.cpp` | `main.py` |
| `brute.cpp` | `brute.py`（可选） |
| `gen.py` | `gen.py`（不变） |

#### 代码嵌入

`index.md` 中的代码引用改为：

```markdown
### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.py, python)

### 代码

@include-code(./main.py, python)
```

#### Tags

- 必须包含 `python` 标签
- 保留算法相关标签（如 `贪心`、`动态规划`、`图论` 等）
- 示例：`tags: ["贪心", "python", "分类讨论"]`

#### 文章结构

`index.md` 在标准章节之后、`### 总结` 之前，增加 Python 教学板块：

```markdown
### 题意

### 思路

@include-code(./brute.py, python)

（算法推导...）

### Python 知识

（从 python-oj-learn 阶段的教学内容中提取：）
- 本题用到的 Pythonic 模式和标准库用法
- C++ → Python 对照（如果用户熟悉 C++）
- 模仿清单：2-4 个值得记住的 Python 写法

### 代码

@include-code(./main.py, python)

### 复杂度

### 总结
```

#### 过程文档适配

`problem-analysis-workspace/` 中的文档内容适配 Python：

- `03-solution-derivation.md`：用 Python 代码说明实现对应关系
- `05-complexity-and-implementation.md`：说明 Python 特有的性能考量（输入速度、递归限制、对象开销等）
- `06-final-index-draft.md`：包含 `### Python 知识` 章节

#### brute.py 规则

- `brute.py` 是可选的（不像 C++ 文章那样强制要求）
- 如果写了 `brute.py`，保持简短，用于教学和对拍
- 如果问题不适合 Python 暴力（如搜索空间太大），可以跳过
- 跳过时在 `03-solution-derivation.md` 中记录原因

#### 对拍

- 使用 `brute.py` + `main.py` + `gen.py` 进行对拍
- 对拍命令适配 Python：
  ```bash
  python3 scripts/problem-analysis-tools/duipai.py \
    --gen problems/<oj>/<problem_id>/gen.py \
    --user "python3 problems/<oj>/<problem_id>/main.py" \
    --brute "python3 problems/<oj>/<problem_id>/brute.py" \
    -n 200
  ```
- 如果 `duipai.py` 不支持自定义命令，可以手写对拍脚本

#### 不创建 C++ 文件

- 不创建 `main.cpp`、`brute.cpp`
- 不引用 `oj-cpp-competitive-style` skill

### 不变的部分

以下 `oj-problem-analysis-writer` 规则保持不变：

- frontmatter 格式和字段要求
- 新建文章的 frontmatter 在 `tags` 后包含 `favorite: false` 和 `favorite_reason: ""`；二者记录个人学习启发，不并入算法 tags
- `[[TOC]]` 和固定章节标题
- `description` 非空要求
- `difficulty` 评估要求
- 可视化评估和 AI 一图流评估
- 一致性检查流程
- `oj-problem-format-spec` 的所有格式要求

## 工作流总结

```
用户输入题目
    │
    ▼
┌─────────────────────────────┐
│ 阶段一：python-oj-learn     │
│  1. 读题面                   │
│  2. 检索 Python 笔记         │
│  3. 写 main.py + brute.py    │
│  4. 验证样例                  │
│  5. 输出教学内容              │
└──────────────┬──────────────┘
               │
               ▼
┌─────────────────────────────┐
│ 阶段二：oj-problem-analysis  │
│ -writer（Python 适配）       │
│  1. 写 workspace 文档         │
│  2. 写 index.md（含 Python    │
│     知识章节）                │
│  3. 一致性检查                │
│  4. AI 一图流评估             │
└──────────────┬──────────────┘
               │
               ▼
         完成题解文章
```

## 最终回复

完成后报告：

- 题目目录路径
- `main.py` 是否创建，核心算法是什么
- `brute.py` 是否创建，或跳过原因
- `index.md` 是否包含 `### Python 知识` 章节
- 使用了哪些 Python 笔记文章（绝对路径）
- tags 列表（必须含 `python`）
- description 内容
- 对拍是否运行
- 可视化评估结果
