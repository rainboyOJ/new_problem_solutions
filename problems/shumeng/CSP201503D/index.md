---
oj: "shumeng"
problem_id: "CSP201503D"
title: "网络延时"
description: "将交换机和电脑建成一棵树，通过两次 BFS 求树的直径。"
difficulty: "普及-"
date: 2026-07-31 16:21
toc: true
tags: ["树", "BFS", "树的直径"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201503D
---

[[TOC]]

### 题意

交换机组成树，每台电脑作为叶子接到一台交换机上，求任意两台设备之间的最大距离。

### 思路

先看从每个节点 BFS 的小数据基准：

@include-code(./brute.cpp, cpp)

整个网络仍是一棵树，答案是树的直径。从任意节点 BFS 找最远点 `u`，再从 `u` BFS，第二次的最远距离就是直径。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设总节点数为 $N=n+m$，时间复杂度为 $O(N)$，空间复杂度为 $O(N)$。

### 总结

把挂在交换机上的电脑也当作树节点，题目就变成标准树直径。两次 BFS 是无权树直径的线性做法。
