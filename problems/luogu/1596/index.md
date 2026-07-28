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

### 思路二：两次 BFS（教学版）

标准做法是一次 BFS 同时完成探索和标记。下面换一种写法：**把"判断"和"标记"拆成两次独立的 BFS**。

- **第一次 BFS**：从当前 `W` 格子出发，用独立的 `vis[][]` 数组遍历整个连通分量。这次 BFS **不修改网格**，只判断该点能不能"走出去"（即是否发现一个新水塘）。
- **第二次 BFS**：确认是新水塘后，再做一次 BFS，把整个连通分量的格子改为 `'2'`（flood fill）。

这样做的教学意义在于：第一次 BFS 只负责发现，第二次 BFS 只负责标记，逻辑更清晰。

@include-code(./main2.cpp, cpp)

### Python 知识

- 字符串不可修改，因此读取成 `list(input())` 的字符列表。
- 八个方向用列表推导式生成。
- `deque` 提供 $O(1)$ 的 `popleft`。
- 直接修改网格代替额外 `visited` 矩阵，减少一份状态。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`deque` 队列。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/bfs_shortest.md`：网格邻居与 BFS 骨架。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### 复杂度

每个格子最多入队一次，时间和空间复杂度均为 $O(nm)$。

### 总结

统计连通块的固定模式是“发现一个未访问目标点，答案加一，再搜索并标记整个连通块”。本题只是把邻接方向改成八方向。
