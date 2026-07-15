---
oj: "luogu"
problem_id: "P1249"
title: "最大乘积"
description: "从 2 开始拆成尽量多的互不相同自然数，再把剩余值从大到小分散加回以最大化乘积。"
difficulty: "普及-"
date: 2026-07-15 22:10
toc: true
tags: ["贪心", "高精度", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1249
---

[[TOC]]

### 题意

把正整数 `n` 拆成若干个互不相同的自然数之和，使这些数的乘积最大。输出拆分方案和最大乘积。

### 思路

乘积最大时，应尽量拆成多个接近的数，并避免使用 `1`。因此从 `2,3,4,...` 开始尽量取：

```text
2 + 3 + 4 + ...
```

直到再取下一个数会超过 `n`。此时剩下 `remaining`，把它从当前较大的数开始每次加 `1` 分散回去。

例如 `n=10`：

```text
先取 2,3,4，和为 9，剩 1
把 1 加到最大数 4 上，得到 2,3,5
```

这样仍然互不相同，并且数值尽量均衡。乘积可能很大，但 Python 大整数可以直接计算。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：Python 整数不会溢出，适合计算大乘积。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：`print(*parts)` 按空格输出方案。
- 列表可以从末尾向前循环分配剩余量。

### 代码

@include-code(./main.py, python)

### 复杂度

拆出的项数约为 $O(\sqrt n)$，时间复杂度 $O(\sqrt n)$，空间复杂度 $O(\sqrt n)$。

### 总结

本题的核心是贪心拆分：先取尽量多的连续不同数，再把余数分散给较大的项，让整体更均衡。
