---
oj: "luogu"
problem_id: "P1596"
title: "[USACO10OCT] Lake Counting S"
description: "扫描网格，每遇到未访问水格就用八方向 BFS 淹掉整个连通块并把答案加一。"
difficulty: "普及-"
date: 2026-07-16 18:01
toc: true
tags: ["BFS", "flood fill", "网格", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1596
---

[[TOC]]

### 题意

字符网格中，八方向相邻的所有 `W` 属于同一个水塘，统计水塘数量。

### 思路

从上到下扫描网格。每遇到一个仍为 `W` 的格子，它一定属于一个尚未统计的新连通块，于是答案加一，并从这里 BFS 找到整块水域。

访问水格时直接把它改成 `.`。这同时完成了访问标记，后续扫描和 BFS 都不会再次处理它。

### Python 知识

- 字符串不可修改，因此读取成 `list(input())` 的字符列表。
- 八个方向用列表推导式生成。
- `deque` 提供 $O(1)$ 的 `popleft`。
- 直接修改网格代替额外 `visited` 矩阵，减少一份状态。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`deque` 队列。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/bfs_shortest.md`：网格邻居与 BFS 骨架。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

deque：

@include-code(./main-pythonic.py, python)

### 复杂度

每个格子最多入队一次，时间和空间复杂度均为 $O(nm)$。

### 总结

统计连通块的固定模式是“发现一个未访问目标点，答案加一，再搜索并标记整个连通块”。本题只是把邻接方向改成八方向。
