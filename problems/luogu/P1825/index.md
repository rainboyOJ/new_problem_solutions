---
oj: "luogu"
problem_id: "P1825"
title: "[USACO11OPEN] Corn Maze S"
description: "预处理每个传送门端点的另一端，BFS 进入字母格时立即跳转并只增加一次移动时间。"
difficulty: "普及/提高-"
date: 2026-07-16 18:01
toc: true
tags: ["BFS", "网格", "最短路", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1825
---

[[TOC]]

### 题意

在玉米迷宫中从 `@` 到 `=`。移动到相邻格花一单位时间；踏上成对大写字母后必须立即免费传送到另一个同字母端点。

### 思路

先扫描迷宫，按字母把大写传送门坐标存进 `vector`（每字母恰好两个位置）。

BFS 尝试走入相邻格：若不是墙且未被访问过，就进一步判断——如果是大写字母，则从 `vector` 中找到同字母的另一端跳转过去，再入队；否则直接入队。无论是否触发传送，步数都只加一。

因为步数代价统一为 `1`，普通 BFS 就能求出最短路。

### Python 知识

- `defaultdict(list)` 按字母收集两个端点。
- 字典推导式配合 `enumerate(pair)` 同时建立两个方向的映射。
- `cell.isupper()` 直接识别大写字母传送门。
- 坐标元组可同时作为字典键、集合元素和队列状态。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`defaultdict`、集合与 `deque`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/bfs_shortest.md`：网格最短路状态。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### 复杂度

预处理和 BFS 都至多扫描常数次网格，时间与空间复杂度均为 $O(nm)$。

### 总结

免费传送不需要额外入队一层：在生成邻居时直接把端点规范成另一端，就能继续使用普通 BFS 的层数作为时间。
