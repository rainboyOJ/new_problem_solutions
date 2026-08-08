---
oj: "luogu"
problem_id: "P1403"
title: "[AHOI2005] 约数研究"
description: "交换约数统计顺序得到 sum floor(n/d)，再按相同商的连续区间整段求和。"
difficulty: "普及+/提高"
date: 2026-07-16 19:20
toc: true
tags: ["整除分块", "约数", "数论", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1403
---

[[TOC]]

### 题意

求 `1..n` 每个整数约数个数的总和。

### 思路

约数 `d` 会成为 `d,2d,...` 共 `floor(n/d)` 个数的约数，因此交换统计顺序：

$$\sum_{i=1}^n f(i)=\sum_{d=1}^n\left\lfloor\frac nd\right\rfloor$$

还可以利用整除分块。对于当前 `left`，商 `q=n//left` 在连续区间 `[left,n//q]` 内不变，整段贡献为 `q*(right-left+1)`，然后跳到下一段。

### Python 知识

- `//` 是整数向下除法，直接对应公式中的下取整。
- `divmod` 不需要用于这里，因为商相同区间右端可由 `n//quotient` 得到。
- Python 大整数安全累加约数总数。
- `while left<=n` 按块跳跃，循环次数约为 `2*sqrt(n)`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：整数除法和任意精度。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：从逐项求和到按块归并。

### 代码
@include-code(./main.py, python)

@include-code(./main.cpp, cpp)


### 复杂度

整除分块时间复杂度 $O(\sqrt n)$，额外空间 $O(1)$。

### 总结

从“每个数有多少约数”切换为“每个约数出现多少次”得到调和和，再按相同商分块可继续加速。
