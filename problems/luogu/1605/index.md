---
oj: "luogu"
problem_id: "P1605"
title: "迷宫"
description: "用 DFS 枚举从起点到终点的所有简单路径，进入格子时标记、返回时撤销。"
difficulty: "普及-"
date: 2026-07-16 18:01
toc: true
tags: ["DFS", "回溯", "网格", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1605
---

[[TOC]]

### 题意

在最多 `5x5` 的网格中，从起点上下左右移动到终点。障碍不能进入，每个格子最多经过一次，统计不同路径数量。

### 思路

网格很小，可以直接 DFS 枚举路径。到达终点时当前选择序列形成一条合法路径，返回 `1`；否则尝试四个方向，把所有子问题返回的路径数相加。

进入下一格前加入 `visited`，递归返回后删除。这一步撤销非常重要，否则当前分支访问过的格子会错误地阻止其他路径使用。

### Python 知识

- 坐标写成 `(x,y)` 元组，可直接放入 `blocked` 和 `visited` 集合。
- `routes += dfs(*nxt)` 用 `*` 把坐标元组解包成两个参数。
- `set.add` 与 `set.remove` 对应回溯的选择和撤销。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：DFS 回溯与状态恢复。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：元组状态与集合判重。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

推导式：

@include-code(./main-pythonic.py, python)

### 复杂度

最坏需要枚举指数级简单路径，可粗略记为 $O(4^{nm})$；递归栈和访问集合为 $O(nm)$。

### 总结

这题不是求最短路，而是统计所有不重复经过格子的路径，因此必须用回溯，在每个分支结束后恢复访问状态。
