---
oj: "luogu"
problem_id: "P1009"
title: "[NOIP 1998 普及组] 阶乘之和"
description: "用 Python 大整数逐步维护当前阶乘，并累加得到 1! 到 n! 的和。"
difficulty: "普及-"
date: 2026-07-15 18:22
toc: true
tags: ["python", "入门", "循环", "高精度", "数学"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1009
---

[[TOC]]

### 题意

输入 `n`，计算：

$$
1!+2!+3!+\cdots+n!
$$

其中 `n <= 50`，结果可能超过普通 64 位整数范围。

### 思路

Python 的 `int` 是任意精度整数，所以不需要手写高精度数组。可以一边维护当前阶乘，一边累加答案：

```python
factorial *= x
answer += factorial
```

当 `x` 从 `1` 到 `n` 递增时，`factorial` 依次变成 `1!, 2!, 3!, ...`。

旧目录中只有空 C++ 模板；本篇补成 Python 教学，重点是 Python 大整数和递推式循环。`brute.py` 不单独写，因为递推累加就是完整解法。

### Python 知识

- Python `int` 不会像 C++ `long long` 那样固定 64 位溢出。
- `range(1, n + 1)` 产生 `1..n`。
- `factorial *= x` 可以从上一个阶乘得到当前阶乘，避免每次从头乘。
- `answer += factorial` 累加阶乘和。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：Python 任意精度整数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：整数输入输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：循环与聚合思想。

### 代码

@include-code(./main.py, python)

### 复杂度

循环 `n` 次。由于整数会变大，单次乘法和加法的实际成本随位数增长；在本题 `n <= 50` 下完全足够。

### 总结

Python 很适合用来学习这类高精度入门题。先利用语言自带的大整数把递推关系写清楚，再理解手写高精度会更容易。
