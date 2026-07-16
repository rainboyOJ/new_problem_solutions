---
oj: "luogu"
problem_id: "P1226"
title: "【模板】快速幂"
description: "使用 Python 三参数 pow 直接计算模意义下的快速幂。"
difficulty: "普及-"
date: 2026-07-16 18:28
toc: true
tags: ["数学", "快速幂", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1226
---

[[TOC]]

### 题意

计算 $a^b\bmod p$，并按指定格式输出。

### 思路

快速幂把指数写成二进制，只使用 $O(\log b)$ 次平方和乘法。Python 已经在内置函数中实现了这一算法：

```python
pow(a, b, modulus)
```

三参数版本会在运算过程中持续取模，不会先构造可能极大的 `a ** b`。OJ 中应优先使用它，而不是写成 `a ** b % modulus`。

### Python 知识

- `pow(base, exponent, modulus)` 是模快速幂，复杂度为 $O(\log exponent)$。
- f-string 可以直接拼出题目要求的固定格式。
- Python 内置 `pow` 由底层高效实现，模板题没有必要手写循环来代替它。

### 代码

@include-code(./main.py, python)

原有手写 C++ 快速幂仍可用于理解二进制拆分：

@include-code(./main.cpp, cpp)

### 复杂度

时间 $O(\log b)$，除大整数运算内部空间外只使用 $O(1)$ 个变量。

### 总结

这题最能体现 Python 相对 C++ 的语言特性：三参数 `pow` 就是可直接提交的标准模快速幂。
