---
oj: "luogu"
problem_id: "P1719"
title: "最大加权矩形"
description: "枚举矩形上下边界并压缩列和，再用 Kadane 算法求每个行带的最大连续子段和。"
difficulty: "普及+/提高"
date: 2026-07-16 17:48
toc: true
tags: ["动态规划", "前缀和", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1719
---

[[TOC]]

### 题意

在 $n\times n$ 整数矩阵中选择一个非空子矩形，使元素和最大。

### 思路

枚举矩形的上、下边界，把这几行按列累加成一维数组。此时选择左右边界就等价于求一维最大连续子段和。

固定样例的第 $2$ 到第 $4$ 行后，列和为 `[4, 11, -10, 1]`。`dp` 表示“必须以当前列结尾”的最大和：

| 列 | 当前列和 | `dp = max(value, dp + value)` | 全局最优 |
| --- | ---: | ---: | ---: |
| 1 | 4 | 4 | 4 |
| 2 | 11 | 15 | 15 |
| 3 | -10 | 5 | 15 |
| 4 | 1 | 6 | 15 |

表中第 2 列得到样例答案 $15$。逐步增加下边界时原地更新 `column_sum`，不必重新求列和。

### Python 知识

- `enumerate(row)` 同时取得列号和元素，适合原地累计列和。
- `max(value, current + value)` 是 Kadane 状态转移，普通循环比强行使用 `reduce` 更清楚。
- 二维列表必须逐行创建，避免浅拷贝问题。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n^3)$，空间复杂度 $O(n^2)$。

### 总结

二维最大子矩形的核心是枚举行带，把二维选择降成一维最大子段和。
