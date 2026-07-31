---
oj: "shumeng"
problem_id: "CSP201512D"
title: "送货"
description: "检查固定起点的欧拉路条件后，按邻接点升序执行 Hierholzer 构造字典序最小路径。"
difficulty: "普及+/提高"
date: 2026-07-31 16:21
toc: true
tags: ["欧拉路径", "图论", "贪心"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201512D
---

[[TOC]]

### 题意

从 1 号点出发经过无向图每条边恰好一次，并输出字典序最小的路口序列。

### 思路

欧拉路要求奇度点数为 0 或 2；若有 2 个奇度点，起点 1 必须是其中之一。将每个邻接表按终点升序排序，Hierholzer 算法每次走当前最小的未用边，回溯时记录顶点，反转后得到字典序最小欧拉路。若最终顶点数不是 `m+1`，图不连通而无解。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

排序为 $O(m\log m)$，构造为 $O(n+m)$；空间复杂度为 $O(n+m)$。

### 总结

欧拉路的奇度条件只保证可能性，仍须检查从 1 出发是否使用了所有边。边按编号标记，避免无向边被重复走。
