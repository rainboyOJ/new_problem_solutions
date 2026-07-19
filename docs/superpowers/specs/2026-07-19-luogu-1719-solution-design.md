# Luogu P1719 题解完善设计

## 背景

`problems/luogu/1719/main.py` 已使用行带压缩与 Kadane 算法，但列累加写法还可以更贴近 Python 习惯。现有 `main.cpp`、`brute.cpp` 和 `gen.py` 是空壳，`index.md` 又直接从固定上下边界跳到一维 DP，没有解释二维矩形为什么能压缩成连续子段。

## 目标

- 简化 `main.py`，保持 $O(n^3)$ 时间复杂度与全负矩阵的正确性。
- 完成清楚的 C++17 正解 `main.cpp`。
- 完成按题意直接枚举的小数据 `brute.cpp` 和随机生成器 `gen.py`。
- 重写 `index.md`，让读者能从朴素枚举自然推导出行带压缩与 Kadane。
- 同步更新过程文档，并用样例和随机对拍验证两种正式实现。

## 非目标

- 不引入比 $O(n^3)$ 更复杂的算法。
- 不修改 P1719 之外的题目文件。
- 不维护未经验证的题目关系或外部推荐链接。
- 不生成 AI 一图流；DP 教学使用确定性的 Markdown 表格。

## 算法设计

一个非空子矩形由 `top`、`bottom`、`left`、`right` 四条边确定。固定 `top` 和 `bottom` 后，把这几行的同一列相加，得到一维数组：

$$
column\_sum[j]=\sum_{i=top}^{bottom}a[i][j].
$$

此时选择原矩形的左右边界，等价于在 `column_sum` 中选择一个非空连续子段。对这个数组运行 Kadane：

$$
dp_j=\max(column\_sum[j],dp_{j-1}+column\_sum[j]).
$$

枚举所有上下边界需要 $O(n^2)$ 组，每组更新列和并扫描 Kadane 需要 $O(n)$，总时间复杂度为 $O(n^3)$。

## 代码设计

### Python

- 按行读取矩阵。
- 对每个 `top` 初始化全零 `column_sum`。
- 使用 `zip(column_sum, row)` 和列表推导式逐行累加。
- 使用 `current = max(current, 0) + value` 表达“重新开始或接在前面”。
- `answer` 初始化为负无穷，保证全负矩阵仍选择一个非空矩形。

### C++

- 使用全局 `matrix` 和 `column_sum` 数组，避免大数组放栈上。
- 使用普通三层循环枚举 `top`、`bottom` 和列。
- Kadane 状态和 Python 保持一致，并添加状态含义与全负边界的中文注释。
- 遵循 C++17 竞赛风格，不使用 lambda、结构化绑定或复杂封装。

### 暴力与生成器

- `brute.cpp` 枚举四条边，再逐格计算矩形和；复杂度高但最贴近题意。
- `gen.py` 生成 $1\leqslant n\leqslant 6$ 的随机矩阵，数值同时覆盖负数、零和正数。
- 暴力不使用行带压缩或 Kadane，确保验证路径独立。

## 文章设计

`index.md` 按以下顺序讲解：

1. 矩形由四条边确定，直接逐格求和为什么太慢。
2. 固定上下边界后，矩形只剩左右边界需要选择。
3. 把行带按列相加，证明矩形和等于压缩数组的连续子段和。
4. 用样例第 2 至第 4 行算出 `[4, 11, -10, 1]`。
5. 用 DP 表解释 Kadane 每一列的“重新开始”和“接在前面”两种选择。
6. 说明逐步下移 `bottom` 时如何增量更新列和。
7. 给出正确性、全负矩阵边界、复杂度以及 C++/Python 代码入口。

正式代码章节包含 `main.cpp` 和 `main.py` 两个引用；朴素部分引用 `brute.cpp`。frontmatter 使用已有准确字段，标签调整为与最终内容一致的 `动态规划`、`矩阵`、`枚举`、`python`。

## 验证设计

- 编译 `main.cpp` 和 `brute.cpp`，启用 C++17 与常用警告选项。
- 运行官方样例，要求 C++、Python 和暴力输出均为 `15`。
- 检查 $n=1$、全负矩阵、全正矩阵和答案为单个元素的边界。
- 使用固定种子随机数据，分别将 C++ 与 Python 正解和 `brute.cpp` 严格对拍至少 200 组。
- 运行 Python 语法检查、`check_problem.py`、`git diff --check` 和文章草稿一致性检查。

## 影响文件

- `problems/luogu/1719/main.py`
- `problems/luogu/1719/main.cpp`
- `problems/luogu/1719/brute.cpp`
- `problems/luogu/1719/gen.py`
- `problems/luogu/1719/index.md`
- `problems/luogu/1719/problem-analysis-workspace/*.md`

