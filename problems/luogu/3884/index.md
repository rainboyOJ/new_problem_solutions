---
oj: "luogu"
problem_id: "P3884"
title: "[JLOI2009] 二叉树问题"
description: "BFS 统计层深与宽度，通过父指针求 LCA，并按向上边双倍、向下边单倍计算距离。"
difficulty: "普及/提高-"
date: 2026-07-16 18:17
toc: true
tags: ["二叉树", "BFS", "LCA", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3884
---

[[TOC]]

### 题意

给出根为 `1` 的树，求最大深度、最大层宽，以及指定 `x` 到 `y` 的特殊距离：向根方向每条边代价 `2`，向叶方向每条边代价 `1`。

### 思路

BFS 从根计算每个节点深度；相同深度的节点数用 `Counter` 统计，最大频率就是宽度。

求距离时，先把 `x` 到根的全部祖先放入集合，再让 `y` 沿父指针上升，第一个属于集合的节点就是 LCA。于是：

$$
2(depth_x-depth_{lca})+(depth_y-depth_{lca})
$$

### Python 知识

- `Counter(depth[1:])` 直接统计每层节点数。
- 祖先集合提供平均 $O(1)$ 成员判断，适合 `n<=100` 的朴素 LCA。
- `print(...,sep="\n")` 一次输出三个独立答案。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`Counter`、集合与 `deque`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/bfs_shortest.md`：层次 BFS。

### 代码

@include-code(./main.py, python)


### 复杂度

BFS 与两条祖先链均为 $O(n)$，空间复杂度 $O(n)$。

### 总结

树上距离先找 LCA 再拆成“向上段”和“向下段”；本题两种方向权值不同，不能直接用普通边数公式。
