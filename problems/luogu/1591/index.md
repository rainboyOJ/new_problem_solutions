---
oj: "luogu"
problem_id: "P1591"
title: "阶乘数码"
description: "预处理到最大 n 的阶乘，用 Python 大整数转字符串后统计指定数字出现次数。"
difficulty: "入门"
date: 2026-07-15 22:10
toc: true
tags: ["高精度", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1591
---

[[TOC]]

### 题意

多组询问，每组给出 `n` 和一个数码 `a`，求 `n!` 的十进制表示中 `a` 出现了多少次。

### 思路

`n <= 1000`，Python 的大整数可以直接保存 `1000!`。为了避免每组询问都重新算阶乘，先找到所有询问中的最大 `n`，预处理：

```python
factorials[i] = factorials[i-1] * i
```

回答时把 `factorials[n]` 转成字符串，用 `count(digit)` 统计。

这题是 Python 大整数和字符串统计练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：Python `int` 支持任意精度整数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：多组输入可以用 `sys.stdin.read().split()` 统一读取。
- `str(big_number).count(digit)` 可以统计字符出现次数。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sys.stdin 快读：

@include-code(./main-pythonic.py, python)

### 复杂度

预处理到最大 `n` 需要做 `max_n` 次大整数乘法。每组询问需要把对应阶乘转字符串并统计，复杂度与数字位数有关。

### 总结

Python 处理高精度阶乘题很直接：先用大整数算出结果，再把十进制表示当字符串处理。
