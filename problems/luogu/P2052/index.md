---
oj: "luogu"
problem_id: "P2052"
title: "[NOI2011] 道路修建"
description: "任选根 DFS 求每棵子树大小，边费用 = 边权 × |2·子树大小 − n|，一次遍历累加总费用。"
difficulty: "普及"
date: 2026-07-17 02:00
toc: true
tags: ["树形 DP", "子树大小", "前向星"]
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

于是一次迭代 DFS（前向星存边，避免深递归爆栈）得到遍历顺序，逆序回推每个节点的子树大小，同时累加每条父边的费用，整棵树只扫一遍。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

- 时间：一次遍历 + 逆序汇总，$O(n)$。
- 空间：前向星与子树大小数组，$O(n)$。

## 总结

"树边分割"类问题通常只需要知道一侧的子树大小，另一侧由总数减去它得到。用根化把无根树变成有向的父子关系，再自底向上回推子树大小，是最直接的 $O(n)$ 解法。注意费用和要使用 64 位整数。
