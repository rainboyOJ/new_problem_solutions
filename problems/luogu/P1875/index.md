---
oj: "luogu"
problem_id: "P1875"
title: "佳佳的魔法药水【数据有误】"
description: "对配方超边做 Dijkstra 式松弛，再按最小成本递增顺序统计最优方案数。"
difficulty: "提高"
date: 2026-07-17 03:00
toc: true
tags: ["最短路", "Dijkstra", "计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1875
---

[[TOC]]

### 题意

药水可直接购买，也可由两份药水合成；求 0 号药水最小成本和最优方案数。

### 思路

初始距离是购买价格。某原料成本确定或下降时，检查包含它的配方 `A+B->C`，用 `cost[A]+cost[B]` 松弛 `C`。最小成本确定后，最优配方的原料成本都严格小于成品，按成本排序即可从低到高统计购买方案和合成方案。

### Python 知识

- EOF 输入用 `read().split()`，每三个整数切成一个配方元组。
- `heapify` 一次把所有购买方案放入堆。
- 生成器求和表达 `ways[A]*ways[B]` 的配方组合数。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

最短成本约 `O((n+r)log n)`，计数 `O(n log n+r)`，空间 `O(n+r)`。

### 总结

二元配方是“两个前驱同时到齐”的超边，仍可用单调成本顺序处理。
