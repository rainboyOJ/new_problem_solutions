---
oj: "luogu"
problem_id: "P2241"
title: "统计方形（数据加强版）"
description: "先用公式统计所有矩形，再枚举边长统计正方形，二者相减得到非正方形长方形。"
difficulty: "入门"
date: 2026-07-15 21:30
toc: true
tags: ["数学", "组合计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2241
---

[[TOC]]

### 题意

给定一个 `n x m` 的方格棋盘，统计其中包含多少个正方形，以及多少个长方形。这里“长方形”不包含正方形。

### 思路

先统计正方形。

如果正方形边长为 `side`，它的左上角有：

```text
(n - side + 1) * (m - side + 1)
```

种放法。枚举 `1..min(n,m)` 的所有边长并求和，就是正方形总数。

再统计所有矩形。一个矩形由两条横向网格线和两条纵向网格线决定：

```text
C(n + 1, 2) * C(m + 1, 2)
= n * (n + 1) * m * (m + 1) // 4
```

所有矩形数量减去正方形数量，就是题目要求的非正方形长方形数量。

### Python 知识

- Python 的 `int` 是任意精度整数，不用担心这里的计数超过 C++ `int`。
- `//` 是整数除法，适合写组合计数公式。
- `range(1, min(n, m) + 1)` 用来枚举所有可能的正方形边长。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度为 $O(\min(n,m))$，空间复杂度为 $O(1)$。

### 总结

方格计数题要优先想“选边界”。所有矩形用选两条横线和两条竖线统计，正方形再按边长单独统计。
