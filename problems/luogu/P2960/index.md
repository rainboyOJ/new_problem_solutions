---
oj: "luogu"
problem_id: "P2960"
title: "[USACO09OCT] Invasion of the Milkweed G"
description: "从初始格做八方向 BFS，最远可达草地的距离就是完全侵占周数。"
difficulty: "普及-"
date: 2026-07-16 20:10
toc: true
tags: ["BFS", "网格", "deque", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2960
---

[[TOC]]

### 题意

乳草每周向周围八格的非岩石地扩散，求占领最后一块草地的时间。

### 思路

每次扩散代价都是一周，多源波次实际只有一个初始格，因此普通 BFS 求出的格子距离就是首次被占领时间，答案为最大距离。

输入地图从上到下，而起点坐标以左下为原点，所以起始行要转换为 `height - start_y`。

### Python 知识

- `deque` 做 BFS 队列。
- 字典 `distance` 同时判重和保存周数。
- 两层 `for dr/dc in (-1,0,1)` 简洁枚举八邻域；原格因已访问会自动跳过。

### 代码

@include-code(./main.py, python)

### 复杂度

每格至多访问一次，时间和空间均为 $O(XY)$。

### 总结

“同步每周扩散”就是无权图最短距离波次，最后完成时间等于最远点距离。
