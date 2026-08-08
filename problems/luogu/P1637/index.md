---
oj: "luogu"
problem_id: "P1637"
title: "三元上升子序列"
description: "离散化后用两次 Fenwick 扫描统计每个中间位置左侧更小和右侧更大的数量。"
difficulty: "普及+/提高"
date: 2026-07-16 23:59
toc: true
tags: ["树状数组", "离散化", "计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1637
---

[[TOC]]

### 题意

统计 `i < j < k` 且 `a[i] < a[j] < a[k]` 的三元组数量。

### 思路

固定中间位置 `j`。左侧比 `a[j]` 小的个数乘右侧比它大的个数，就是以 `j` 为中间点的方案数。离散化后，正向 Fenwick 查询严格更小的排名，反向 Fenwick 查询严格更大的排名，最后求乘积之和。

### Python 知识

- `sorted(set(values))` 加字典推导式完成离散化。
- 反向扫描时用 `seen - prefix(rank)` 处理严格大于，避免重复值被计入。
- `zip(left_count, right_count)` 直接组合两个计数列表。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

离散化 `O(n log n)`，两次 Fenwick 扫描 `O(n log n)`，空间 `O(n)`。

### 总结

三元组计数的关键是固定中间点，把三维条件拆成两个一维前缀统计。
