---
oj: "luogu"
problem_id: "P1875"
title: "佳佳的魔法药水【数据有误】"
description: "对配方超边做 Dijkstra 式松弛，再按最小成本递增顺序统计最优方案数。"
difficulty: "提高"
date: 2026-07-17 03:00
updated: 2026-10-06 07:45
toc: true
tags: ["最短路", "Dijkstra", "计数", "python"]
categories: []
pre:
  - oj: "roj"
    problem_id: "1382"
    reason: "B 复用 A 教的堆优化 Dijkstra「按距离从小到大定型」单调序：A 证明候选距离最小者一次定型，B 照此先按最小成本弹出定型药水（main.py 同样用小根堆加 current!=distance 跳过过期条目），再按成本从小到大统计配方超边的松弛与最优方案数，额外叠加的只是 A+B->C 超边建模与方案计数这一层 A 未讲的流程。"
  - oj: "luogu"
    problem_id: "P4779"
    reason: "B 复用 A 的堆取当前最小距离并松弛的 Dijkstra 主循环，把单前驱出边松弛扩成两个前驱到齐才松弛的配方超边"
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
