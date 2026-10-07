---
oj: "codeforces"
problem_id: "19D"
title: "Points"
description: "离线压缩坐标，外层线段树寻找最左可行 x，组内 Fenwick 找最小可行 y。"
difficulty: "提高+/省选-"
date: 2026-07-16 23:59
updated: 2026-10-06 07:45
toc: true
tags: ["线段树", "树状数组", "坐标压缩", "二维查询", "python"]
favorite: false
favorite_reason: ""
categories: []
pre:
  - oj: "luogu"
    problem_id: "P5250"
    reason: "B 的内层 Fenwick 直接复用 A 的「树状数组二进制提升 kth 找第 rank 小」这一步定位组内坐标，再叠加外层线段树按 x 组维护最大 y 做二维最左可行点查询"
  - oj: "luogu"
    problem_id: "P2234"
    reason: "B 复用 A 教的「离散化坐标 + Fenwick kth 二进制倍增在计数树上找第 k 个」这一步（组内定位大于 query_y 的最小 y），再叠加 A 未教的外层线段树按 x 组维护最大 y 的两层结构与增删点动态维护。"
  - oj: "roj"
    problem_id: "3119"
    reason: "B 内层 bit_kth 直接复用 A 教的树状数组二进制提升求第 k 小，只在外层再叠加线段树把查询扩成二维最左可行点定位"
common: []
recommend: []
source: https://codeforces.com/problemset/problem/19/D
---

[[TOC]]

### 题意

动态加入、删除点；查询严格右上方的点，要求先取最小 `x`，再取该 `x` 下最小 `y`。

### 思路

先读完所有操作，压缩所有可能出现的 `x`，并为每个 `x` 收集可能的 `y`。每个 `x` 组用 Fenwick 维护当前点，外层线段树保存该组当前最大 `y`。查询时在线段树中找第一个 `x > query_x` 且最大 `y > query_y` 的组，再用组内 Fenwick 的前缀计数定位第一个大于 `query_y` 的 `y`。

### Python 知识

- 离线读取请求后用 `sorted(set(...))` 和字典推导式完成坐标压缩。
- Fenwick 的 `kth` 二进制提升可在计数树中找第 `k` 个活跃坐标。
- `bisect_right` 表达严格大于边界，避免手写二分。

### 代码

@include-code(./main.py, python)

### 复杂度

外层查找、组内 Fenwick 和坐标二分均为 `O(log n)`，所以每个操作 `O(log n)`，空间 `O(n)`。

### 总结

二维动态查询可以拆成"外层找最小可行 x，内层找最小可行 y"；离线坐标压缩让两层结构都能使用数组。
