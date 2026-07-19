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

先扫描迷宫，把每个大写字母的两个坐标收集起来，再建立“端点到另一端”的字典。

BFS 尝试走入相邻格：若是墙则跳过；若坐标是传送门端点，就立即把下一状态替换为另一端。整次“走一步并传送”仍只把距离加一。所有边的有效代价因此仍是 `1`，普通 BFS 足够。

### Python 知识

- `defaultdict(list)` 按字母收集两个端点。
- 字典推导式配合 `enumerate(pair)` 同时建立两个方向的映射。
- `cell.isupper()` 直接识别大写字母传送门。
- 坐标元组可同时作为字典键、集合元素和队列状态。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`defaultdict`、集合与 `deque`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/bfs_shortest.md`：网格最短路状态。

### 代码

@include-code(./main.py, python)


### 复杂度

预处理和 BFS 都至多扫描常数次网格，时间与空间复杂度均为 $O(nm)$。

### 总结

免费传送不需要额外入队一层：在生成邻居时直接把端点规范成另一端，就能继续使用普通 BFS 的层数作为时间。
