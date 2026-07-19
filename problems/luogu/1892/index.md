---
oj: "luogu"
problem_id: "P1892"
title: "[BalticOI 2003] 团伙 (Day 2)"
description: "用并查集维护强制朋友关系，答案是朋友关系图的连通分量个数；2N 并查集是其紧凑模板写法。"
difficulty: "普及+/提高"
date: 2026-07-16 18:26
toc: true
tags: ["并查集", "种类并查集", "连通分量", "关系传递", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1892
---

[[TOC]]

### 题意

`n` 个人之间有朋友 `F` 或敌人 `E` 关系。朋友的朋友是朋友，敌人的敌人也是朋友。朋友必须在同一团体，求最多能有多少个团体。

### 思路

本质是：把「必须同团」的人连成图，再数连通分量。每个连通分量是一群被规则强制为朋友的人；让每群单独成团，分量个数就是最大团体数。

#### 写法一：建朋友图 + 并查集数连通分量

更贴近题意，适合作为第一版理解：

1. 读到 `F a b`：在朋友图里连边 `a -- b`（并查集 `union`）。
2. 读到 `E a b`：先记下敌人列表。
3. 对每个人，把他的所有敌人两两连边——因为「敌人的敌人是朋友」。
4. 统计 `1..n` 的连通分量个数。

@include-code(./main2.py, python)

#### 写法二：2N 并查集（模板写法）

为每个人建立对立侧节点：

- `x` 表示人物 `x`；
- `x+n` 表示与 `x` 对立的一侧。

规则：

- `F a b`：只合并 `a` 与 `b`；
- `E a b`：合并 `a` 与 `b+n`，以及 `b` 与 `a+n`。

若两人有共同敌人，会通过对立侧落到同一集合，自动得到「敌人的敌人是朋友」。最后只统计真实人物 `1..n` 的不同代表元。

注意：朋友关系时**不要**再合并 `a+n` 与 `b+n`。多合并对立侧会把不该同团的人连起来，答案偏小（容易只得部分分）。

### Python 知识

- 并查集用列表 `parent` / `size`，循环路径压缩不受递归深度限制。
- `{find(i) for i in range(1, n + 1)}` 用集合推导式统计连通分量。
- 关系 token 可保留为 `bytes`，直接与 `b"F"` 比较。
- 敌人列表 `enemies[i]` 是「按点存邻接」，再统一连边。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：集合推导式与去重。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：迭代替代深递归。

### 代码

正式提交用 2N 并查集：

@include-code(./main.py, python)

### 复杂度

- 写法一：处理敌人两两连边时，每人敌人很少，总复杂度仍可视为 $O((n+m)\alpha(n))$ 量级（本题 $n \le 1000$ 足够）。
- 写法二：每条关系常数次合并，时间 $O((n+m)\alpha(n))$，空间 $O(n)$。

### 总结

这题先想成「建强制朋友关系图，数连通分量」。`main2.py` 把这个模型写直白；`main.py` 用 2N 节点把敌友关系压进同一种并查集合并，是可迁移的种类并查集模板。
