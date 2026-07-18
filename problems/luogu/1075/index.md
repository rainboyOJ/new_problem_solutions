---
oj: "luogu"
problem_id: "P1075"
title: "[NOIP 2012 普及组] 质因数分解"
description: "从 2 试除到整数平方根，找到较小质因数后用 n 除以它得到较大质数。"
difficulty: "入门"
date: 2026-06-18 22:06
toc: true
tags: ["数论", "枚举", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1075
---

[[TOC]]

### 题意

已知正整数 `n` 恰好是两个不同质数的乘积，要求输出这两个质数中较大的那个。

### 思路

如果 `d` 是 `n` 的一个因子，那么 `n // d` 也是另一个因子。两个因子一定一小一大，小的那个不会超过 `sqrt(n)`。

题目保证 `n = p * q`，且 `p`、`q` 是不同质数。我们从 `2` 开始向上试除，遇到第一个能整除 `n` 的 `d`，它就是较小的质因数，于是较大的质数就是：

```text
n // d
```

旧目录中保留了 C++ 暴力枚举版本；Python 教学版使用 `math.isqrt` 控制试除上界，不新增 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `int(input())` 读取单个整数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：`math.isqrt(n)` 返回整数平方根，适合做试除上界。
- `range(2, isqrt(n) + 1)` 覆盖从 `2` 到 `sqrt(n)` 的所有可能小因子。
- `n // d` 是整数除法，表示另一个质因数。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

试除质因数：

@include-code(./main-pythonic.py, python)

### 复杂度

最多试除到 $\sqrt n$，时间复杂度是 $O(\sqrt n)$，空间复杂度是 $O(1)$。

### 总结

这题利用了题目给出的强条件：`n` 只有两个不同质因数。找到较小的那个，较大的答案就直接由除法得到。
