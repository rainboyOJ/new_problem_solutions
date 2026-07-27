---
oj: "luogu"
problem_id: "P1303"
title: "A*B Problem"
description: "利用 Python 任意精度整数，直接读入两个大整数后相乘输出。"
difficulty: "入门"
date: 2026-07-15 21:35
toc: true
tags: ["高精度", "数学", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1303
---

[[TOC]]

### 题意

输入两个不超过 $10^{2000}$ 的非负整数，输出它们的乘积。

### 思路

Python 的 `int` 支持任意精度整数，可以直接完成高精度乘法：

```python
print(a * b)
```

这和 C++ 手写竖式乘法不同，Python 内置整数已经实现了大数运算。本文重点是学习 Python OJ 中如何利用语言特性，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：Python 整数不会溢出，适合处理高精度模板题。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：`int(input())` 能直接解析很长的十进制整数。
- 大整数乘法复杂度和位数有关，不是常数时间。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

大整数乘法：

@include-code(./main-pythonic.py, python)


### 复杂度

设数字位数为 `L`，大整数乘法由 Python 内部实现，复杂度随位数增长。对本题规模可以直接通过。

### 总结

在 Python 中，很多高精度整数题可以直接用内置 `int`。这是一种应当掌握的 OJ 语言优势。
