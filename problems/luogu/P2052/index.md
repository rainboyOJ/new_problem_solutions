---
oj: "luogu"
problem_id: "P2052"
title: "[NOI2011] 道路修建"
description: "两次 DFS：先根化建父子关系，再后序求每棵子树大小，边费用 = 边权 × |2·子树大小 − n|。"
difficulty: "普及"
date: 2026-07-17 02:00
updated: 2026-10-24 11:00
toc: true
tags: ["树形 DP", "子树大小", "DFS"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2052
---

[[TOC]]

## 形式化题目

给定一棵 $n$ 个节点的带权无根树。把每条边断开后，树分成两个连通块，这条边的修建费用定义为边权乘以两侧节点数之差的绝对值。求所有边的修建费用之和。

## 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

`brute.cpp` 对每条边断开后分别 DFS 数出两侧节点数再累加费用，单条边 $O(n)$，总复杂度 $O(n^2)$，只适合小数据。

关键观察：任选 $1$ 号点为根，对于父子边 $(fa, u)$，只需知道 $u$ 的子树大小 `size[u]`——断掉这条边后一侧有 `size[u]` 个节点，另一侧就是 $n - \text{size}[u]$，费用为

$$w \times |2 \cdot \text{size}[u] - n|$$

所以只需两次自顶向下的 DFS 就能收尾：

1. `dfs_build(u)`：以 1 号点为根，先序记下每个点的父亲 `parent_arr[]`，把无根树变成父子关系；
2. `dfs_calc(u)`：后序遍历，`subtree_size[u]` 由所有儿子的子树大小累加得到（含自己 1 个点），在儿子返回后立刻用上面的公式结算父子边费用。

邻接表用 `vector<edge> g[maxn]` 存（树题只有 $n-1$ 条边、只需遍历不需要边编号，比链式前向星直观）；递归深度等于树的深度，$n=10^6$ 的链在判题器 64 MiB 栈下实测通过。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

- 时间：两次 DFS 各访问每个点、每条边常数次，$O(n)$。
- 空间：邻接表 $2(n-1)$ 条边记录 + 父亲、子树大小数组，$O(n)$。

## 总结

"树边分割"类问题通常只需要知道一侧的子树大小，另一侧由总数减去它得到。用根化把无根树变成有向的父子关系，再自底向上回推子树大小，是最直接的 $O(n)$ 解法。注意费用和要使用 64 位整数。
