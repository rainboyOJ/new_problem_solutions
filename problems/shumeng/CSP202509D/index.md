---
oj: "shumeng"
problem_id: "CSP202509D"
title: "造题计划（上）"
description: "利用权值排列把路径 mex 转成路径外节点的最小权值，并用树链剖分查询路径补集最小值。"
difficulty: "提高+/省选-"
date: 2026-07-31 16:21
toc: true
tags: ["树链剖分", "路径查询", "mex"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202509D
difficulty: "未知"
---

[[TOC]]

### 题意

树上每个节点有一个 `0..n-1` 的排列权值，询问路径上权值集合的 mex。

### 思路

由于所有权值恰好构成 `0..n-1` 的排列，路径 mex 就是路径外所有节点权值中的最小值；若路径覆盖整棵树，答案为 `n`。

用树链剖分把路径拆成 `O(log n)` 个连续区间，在剖分序列上建立区间最小值线段树。将这些路径区间按左端点排序，扫描它们之间的空隙并查询最小值，得到路径外最小权值。

小数据程序逐次找出路径并标记权值：

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

预处理 `O(n)`；每次询问拆出 `O(log n)` 个区间并进行区间最小值查询，时间复杂度 `O(log^2 n)`，空间复杂度 `O(n)`。

### 总结

排列性质把 mex 的“从零开始检查”降成了一个全局最小值问题，树链剖分负责把路径和路径补集转成线性序列区间。
