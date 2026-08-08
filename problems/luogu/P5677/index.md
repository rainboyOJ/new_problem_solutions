---
oj: "luogu"
problem_id: "P5677"
title: "[GZOI2017] 配对统计"
description: "按值排序找每个位置的最近值邻居，把好配对转成二维点并离线 Fenwick 查询。"
difficulty: "省选/NOI-"
date: 2026-07-16 21:00
toc: true
tags: ["离线查询", "树状数组", "最近邻", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5677
---

[[TOC]]

### 题意

有序对 `(x,y)` 在 `a[y]` 是 `a[x]` 的全局最近值时为好配对。询问下标区间内包含多少好配对，并按询问编号加权。

### 思路

数值互异。按值排序后，某个数的最近值只可能是相邻的前驱或后继；距离相等时两者都算。因此有序好配对总数至多 `2n`。

把每个有序对变成点 `(max(x,y), min(x,y))`。查询 `[l,r]` 要求第一坐标不超过 `r` 且第二坐标不小于 `l`。按查询右端排序，逐步把第一坐标合格的点加入 Fenwick；已加入总数减去第二坐标小于 `l` 的前缀数就是答案。

### Python 知识

- `sorted(range(n), key=values.__getitem__)` 得到按值排列的原下标。
- `key=lambda query: query[1]` 明确按右端点离线排序。
- 重复二维点不能去重，因为相反方向是两组有序配对。

### 代码

@include-code(./main.py, python)

### 复杂度

排序 $O((n+m)\log n)$，Fenwick 操作 $O((n+m)\log n)$，空间 $O(n+m)$。

### 总结

先证明好配对稀疏，再把“两个下标都在区间”转成二维偏序，是本题关键。
