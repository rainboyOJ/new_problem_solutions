---
oj: "luogu"
problem_id: "CF19D"
title: "Points"
description: "Luogu 无法提交 Codeforces 原题，解析已迁移至 codeforces/19D，本页仅保留入口。"
difficulty: "提高+/省选-"
date: 2026-07-16 23:59
toc: true
tags: ["线段树", "树状数组", "坐标压缩", "二维查询"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/CF19D
---

[[TOC]]

### 题意

动态加入、删除点；查询严格右上方的点，要求先取最小 `x`，再取该 `x` 下最小 `y`。完整教学解析（含 Python 版本与思考过程）已迁移至：

- [[problem: codeforces,19D]] · [CF19D Points 题解](https://codeforces.com/problemset/problem/19/D)

### 思路

离线坐标压缩：每个 `x` 组用 Fenwick 维护活跃 `y`，外层线段树存每组最大 `y`。查询时先在线段树找第一个 `x` 更大且最大 `y` 更大的组，再在组内 Fenwick 找第一个大于 `query_y` 的活跃 `y`（`kth` 二进制提升）。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

外层查找、组内 Fenwick 和坐标二分均为 `O(log n)`，所以每个操作 `O(log n)`，空间 `O(n)`。

### 总结

完整解析已迁移至 [[problem: codeforces,19D]]。
