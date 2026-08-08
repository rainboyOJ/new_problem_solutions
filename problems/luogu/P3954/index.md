---
oj: "luogu"
problem_id: "P3954"
title: "[NOIP 2017 普及组] 成绩"
description: "把百分比权重写成整数权重，避免浮点误差后计算加权总分。"
difficulty: "入门"
date: 2026-07-15 18:02
toc: true
tags: ["python", "入门", "数学", "输入输出"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3954
---

[[TOC]]

### 题意

输入作业成绩 `A`、小测成绩 `B`、期末成绩 `C`，总成绩按 $20\%$、$30\%$、$50\%$ 加权计算，输出整数总分。

### 思路

百分比可以直接换成整数权重：

$$
\text{score}=\frac{2A+3B+5C}{10}
$$

题目保证三项成绩都是 $10$ 的整数倍，所以结果是整数。用整数乘法和整除即可，不需要浮点数。

`brute.py` 不适合这题，因为直接公式就是完整解法，没有搜索或优化过程。

### Python 知识

- `a, b, c = map(int, input().split())` 一次读入三个整数。
- 用 `a * 2 + b * 3 + c * 5` 表示加权和。
- `// 10` 是整数除法；在本题保证下不会丢失有效小数。
- 用整数运算表达百分比，通常比 `0.2 * a` 这类浮点写法更稳。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：多整数输入和基础输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：整数运算和浮点注意事项。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：单个答案输出。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

加权整除：

@include-code(./main-pythonic.py, python)


### 复杂度

只做常数次整数运算，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

遇到百分比权重，如果比例能转成整数，优先使用整数表达式。这样代码更贴近题意，也能避免浮点格式和精度问题。
