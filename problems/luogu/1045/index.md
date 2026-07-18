---
oj: "luogu"
problem_id: "P1045"
title: "[NOIP 2003 普及组] 麦森数"
description: "用对数计算 2^P-1 的位数，用模幂 pow(2,p,10^500) 求最后 500 位。"
difficulty: "普及-"
date: 2026-07-15 22:10
toc: true
tags: ["高精度", "数学", "快速幂", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1045
---

[[TOC]]

### 题意

给定 `P`，输出 `2^P - 1` 的十进制位数，以及它的最后 500 位，不足 500 位时高位补 `0`。

### 思路

位数可以用对数计算：

```text
digits = floor(P * log10(2)) + 1
```

最后 500 位只需要模 `10^500`：

```python
last = (pow(2, P, 10**500) - 1) % (10**500)
```

`pow(base, exp, mod)` 是 Python 内置模幂，不会先构造完整的 `2^P`。

最后把结果用 `zfill(500)` 补足 500 位，每 50 位输出一行。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：`pow(a, b, mod)` 可以高效计算模幂。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串切片适合按固定宽度输出。
- `zfill(500)` 可以在左侧补零到指定长度。
- `math.log10` 用于计算十进制位数。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

推导式：

@include-code(./main-pythonic.py, python)

### 复杂度

模幂复杂度约为 $O(\log P)$ 次大整数模乘，模数固定为 `10^500`。输出固定 500 位。

### 总结

本题不能构造完整的 `2^P`。位数用对数，后 500 位用模幂，这是两个独立问题。
