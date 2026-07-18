---
oj: "luogu"
problem_id: "P2036"
title: "[COCI 2008/2009 #2] PERKET"
description: "枚举所有非空食材组合，计算酸度乘积和苦度总和，取二者差值的最小值。"
difficulty: "入门"
date: 2026-07-15 21:50
toc: true
tags: ["枚举", "组合", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2036
---

[[TOC]]

### 题意

有 `n` 种食材，每种有酸度 `s` 和苦度 `b`。选择至少一种食材后：

- 总酸度是所有 `s` 的乘积；
- 总苦度是所有 `b` 的和。

要求最小化 `abs(总酸度 - 总苦度)`。

### 思路

`n <= 10`，可以枚举所有非空组合。

对每个组合：

1. `sour` 从 `1` 开始，乘上每个食材的酸度；
2. `bitter` 从 `0` 开始，加上每个食材的苦度；
3. 用 `abs(sour - bitter)` 更新答案。

### Python 知识

- `combinations(ingredients, size)` 枚举选 `size` 个食材的所有组合。
- `answer = None` 可以表示“还没有任何候选答案”，避免随便写一个很大的初值。
- 元组解包 `for s, b in chosen` 让代码直接对应酸度和苦度。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`

### 代码

@include-code(./main.py, python)

### Pythonic 写法

combinations：

@include-code(./main-pythonic.py, python)

### 复杂度

一共有 $2^n-1$ 个非空组合，每个组合最多处理 `n` 个食材，时间复杂度为 $O(n2^n)$，空间复杂度为 $O(n)$。

### 总结

数据范围很小，最稳妥的做法就是直接枚举所有非空选择，不要过度设计。
