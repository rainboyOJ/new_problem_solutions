---
oj: "luogu"
problem_id: "P4552"
title: "[Poetize6] IncDec Sequence"
description: "把区间加减转到相邻差分上，统计正差与负差总量即可得到最少操作和最终值种数。"
difficulty: "普及+/提高"
date: 2026-07-16 17:48
toc: true
tags: ["差分", "贪心", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4552
---

[[TOC]]

### 题意

每次给一个区间整体加一或减一，求把序列变成常数序列的最少操作数，以及最少操作下可能的最终常数个数。

### 思路

只看相邻差 `a[i]-a[i-1]`。设所有正差之和为 `positive`，所有负差绝对值之和为 `negative`。一次操作最多同时消去一份正差和一份负差，剩余部分再与序列外侧配对，因此最少操作是两者最大值。

未配对的 `abs(positive-negative)` 份操作可以分配到左右边界，最终常数共有 `abs(positive-negative)+1` 种。

### Python 知识

- `pairwise(sequence)` 直接产生所有相邻元素对。
- 两个生成器分别求正向、负向变化量，公式与代码一一对应。
- Python 整数自动扩容，不需要 C++ 的 `long long` 类型选择。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n)$，空间复杂度 $O(n)$。

### 总结

区间整体变化在差分数组中只影响边界，问题最终只剩正负变化量如何配对。
