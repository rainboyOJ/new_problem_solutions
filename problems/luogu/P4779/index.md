---
oj: "luogu"
problem_id: "P4779"
title: "【模板】单源最短路径（标准版）"
description: "用 heapq 实现带过期状态判断的 Dijkstra，求非负权有向图单源最短路。"
difficulty: "普及+/提高-"
date: 2026-07-17 03:00
updated: 2026-10-16
toc: true
tags: ["Dijkstra", "最短路", "heapq", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4779
---

[[TOC]]

### 题意

求非负权有向图中起点到每个节点的最短距离。

### 思路

Dijkstra 每次从堆中取当前距离最小的状态，尝试松弛所有出边。堆中可能保留旧状态，若弹出的距离不等于数组中的最新距离就跳过。

### Python 知识

- `heapq` 是最小堆，元组按距离优先比较。
- `current != distance[node]` 是无 decrease-key 堆的标准过期判断。
- `print(*distance[1:])` 直接输出一行结果。

### 代码

标准写法：

@include-code(./main.py, python)

零基础逐行注释版（`main-user.py`），适合第一次用 `heapq` 写 Dijkstra 时对照阅读：

@include-code(./main-user.py, python)

该版本用 `type Edge = tuple[int, int]`、`type Graph = list[list[Edge]]` 声明类型别名，阅读时可以直接看出邻接表是「点 → 出边列表」的两层结构，因此 `g[u]` 本身是列表、`for v, w in g[u]` 取出的才是边。注意 `type` 语句需要 Python 3.12 及以上；在旧版本上把它写成 `Edge = tuple[int, int]` 赋值形式即可。

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

时间 `O((n+m)log n)`，空间 `O(n+m)`。

### 总结

非负边权优先使用堆优化 Dijkstra。
