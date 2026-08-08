---
oj: "luogu"
problem_id: "P4408"
title: "[NOI2003] 逃学的小孩 / 数据生成器"
description: "树的直径加任意点到两个直径端点的较小距离，得到最坏寻找时间。"
difficulty: "普及+/提高-"
date: 2026-07-17 02:00
toc: true
tags: ["树的直径", "最短路", "树", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4408
---

[[TOC]]

### 题意

父母先去离 Chris 家较近的两个朋友之一，再去另一个，求所有位置的最坏总路程。

### 思路

固定树直径端点 `A,B`。对 Chris 位置 `C`，最坏路线长度为 `dist(A,B)+min(dist(C,A),dist(C,B))`；取所有 `C` 的最大值即可。三次树遍历得到两端距离数组。

### Python 知识

- `map(min, zip(from_a, from_b))` 同时逐点取两个距离的较小值。
- 带权树仍可用列表遍历，因为树中没有重复访问的边。
- `max(..., key=distance.__getitem__)` 是找最远端点的常用模式。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

时间 `O(n)`，空间 `O(n)`。

### 总结

把“先近后远”的路线长度拆成直径和一个端点较小距离，最坏情况就能由直径刻画。
