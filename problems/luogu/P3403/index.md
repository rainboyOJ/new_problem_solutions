---
oj: "luogu"
problem_id: "P3403"
title: "跳楼机"
description: "以最小步长为模建立余数图，Dijkstra 求每类余数最早可达楼层。"
difficulty: "提高"
date: 2026-07-17 03:00
toc: true
tags: ["同余最短路", "Dijkstra", "数学", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3403
---

[[TOC]]

### 题意

从 1 楼反复增加 `x/y/z`，统计不超过 `h` 的可达楼层数。

### 思路

取最小步长 `base`。对每个模 `base` 的余数，Dijkstra 求能到达的最小楼层 `dist[r]`；此后反复加 `base`，同余且更高的楼层全部可达，贡献为 `(h-dist[r])//base+1`。

### Python 知识

- 余数图只有 `min(x,y,z)` 个节点。
- Python 整数直接支持 `2^63` 范围楼层。
- 生成器求和只统计 `dist<=h` 的余数。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

设 `b=min(x,y,z)`，时间 `O(b log b)`，空间 `O(b)`。

### 总结

巨大数值范围加少量固定步长，常压缩成“每个余数的最小代表”。
