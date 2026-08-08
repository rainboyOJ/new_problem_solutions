---
oj: "luogu"
problem_id: "P5836"
title: "[USACO19DEC] Milk Visits S"
description: "LCA 结合根路径 G 计数，判断一条路径上是否出现指定品种。"
difficulty: "普及+/提高-"
date: 2026-07-17 02:00
toc: true
tags: ["LCA", "前缀和", "树", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5836
---

[[TOC]]

### 题意

判断每条路径上是否有朋友喜欢的牛品种。

### 思路

根为 1，预处理每个节点到根路径上的 G 数量。路径 `a-b` 的 G 数量由 `prefix[a]+prefix[b]-2*prefix[lca]` 加上 LCA 自身修正得到；路径总长度已知，H 数量就是总长度减 G 数量。

### Python 知识

- 品种输入保留为 bytes，`b'G'` 比较无需解码。
- `array("i")` 适合深度、父亲和前缀计数。
- 多个查询答案用 `bytearray` 直接构造二进制字符串。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

预处理 `O(n log n)`，每次查询 `O(log n)`，空间 `O(n log n)`。

### 总结

路径上某类点的出现性可以先数一种，再用路径长度补出另一种。
