---
oj: "luogu"
problem_id: "P1036"
title: "[NOIP 2002 普及组] 选数"
description: "用 itertools.combinations 枚举所有选 k 个数的组合，对每个组合求和并判断是否为素数。"
difficulty: "入门"
date: 2026-07-15 21:30
toc: true
tags: ["枚举", "组合", "素数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1036
---

[[TOC]]

### 题意

给定 `n` 个整数，从中选出 `k` 个数求和。问有多少种选择方式，使得选出的数字之和是素数。

### 思路

`n <= 20`，可以直接枚举所有组合。

Python 中：

```python
combinations(numbers, k)
```

会产生所有“不关心顺序、选 k 个”的方案。对每个方案求和，然后用试除法判断是否为素数。

判断素数时只需要试除到 `sqrt(x)`。为了避免浮点误差，用 `math.isqrt(x)` 得到整数平方根。

### Python 知识

- `itertools.combinations(numbers, k)` 直接枚举所有选 `k` 个数的组合。
- `sum(chosen)` 可以对一个元组求和。
- `math.isqrt(x)` 返回 `floor(sqrt(x))`，适合写整数素数判断。
- 把素数判断写成 `is_prime` 函数，可以让主流程更清楚。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/itertools_recipes.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`

### 代码

@include-code(./main.py, python)

### Pythonic 写法

combinations + 生成器计数：

@include-code(./main-pythonic.py, python)

### 复杂度

一共有 $\binom{n}{k}$ 个组合。设最大组合和为 $S$，素数判断为 $O(\sqrt S)$，总时间复杂度为 $O(\binom{n}{k}\sqrt S)$。空间复杂度为 $O(k)$。

### 总结

这题是学习 `combinations` 的典型题：题目说“任选 k 个，不分顺序”，就可以直接映射到组合枚举。
