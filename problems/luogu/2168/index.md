---
oj: "luogu"
problem_id: "P2168"
title: "[NOI2015] 荷马史诗"
description: "补零后执行 K 叉 Huffman 合并，堆中同时维护权重与子树高度。"
difficulty: "提高+/省选-"
date: 2026-07-16 21:00
toc: true
tags: ["K叉Huffman", "贪心", "heapq", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2168
---

[[TOC]]

### 题意

构造最优 K 进制前缀编码，先最小化加权总长度，再最小化最大码长。

### 思路

K 叉 Huffman 每次合并最小的 K 个权重。完整 K 叉树叶数满足 `(leaf-1) % (K-1)==0`，不足时补权重 0 的虚叶。

堆元素为 `(weight, depth)`。合并费用增加所选权重和，新节点高度是最大子高度加一；元组在权重相同时优先较小高度，得到第二关键字最优。

### Python 知识

- 元组由左到右比较，天然实现两级优先级。
- 列表推导式连续 `heappop` K 次。
- `heapq.heapify` 线性建堆。

### 代码

@include-code(./main.py, python)

### 复杂度

时间 $O(n\log n)$，空间 $O(n)$。

### 总结

K 叉 Huffman 相比二叉版多了“补零使叶数合法”和“同权重按高度决策”两个细节。
