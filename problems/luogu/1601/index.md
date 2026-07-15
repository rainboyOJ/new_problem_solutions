---
oj: "luogu"
problem_id: "P1601"
title: "高精度加法"
description: "利用 Python 任意精度整数，直接读入两个大整数后相加输出。"
difficulty: "入门"
date: 2026-07-15 21:35
toc: true
tags: ["高精度", "数学", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1601
---

[[TOC]]

### 题意

输入两个不超过 $10^{500}$ 的非负整数，输出它们的和。

### 思路

在 C++ 中，这通常需要手写高精度加法。但 Python 的 `int` 是任意精度整数，可以直接保存远大于 `long long` 的整数。

所以本题 Python 解法就是：

1. `int(input())` 读入两个大整数；
2. 输出 `a + b`。

这题的教学目标是认识 Python 大整数，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：Python 的 `int` 不会按 64 位整数溢出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：单行整数输入用 `int(input())`。
- 对大整数做 `+` 运算时，Python 会自动处理进位。

### 代码

@include-code(./main.py, python)

### 复杂度

设数字位数为 `L`，大整数加法时间复杂度是 $O(L)$，空间复杂度是 $O(L)$。

### 总结

Python 写高精度模板题时，可以先直接使用内置 `int`。学习重点是知道它的优势和复杂度，而不是手写进位。
