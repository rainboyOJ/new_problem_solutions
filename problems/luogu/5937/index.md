---
oj: "luogu"
problem_id: "P5937"
title: "[CEOI 1999] Parity Game"
description: "把区间奇偶转成两个前缀异或值的关系，用带异或权并查集在线定位第一条矛盾回答。"
difficulty: "普及+/提高"
date: 2026-07-16 17:48
toc: true
tags: ["并查集", "前缀和", "离散化", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5937
---

[[TOC]]

### 题意

依次给出若干区间中 $1$ 的个数为奇数或偶数的回答，求第一条必然与此前回答矛盾的回答之前有多少条正确回答。

### 思路

设 `prefix[x]` 是前 $x$ 位的异或和，则 `[l,r]` 的奇偶性为 `prefix[l-1] ^ prefix[r]`。每条回答因此约束两个前缀点之间的异或关系。

带权并查集维护节点到根的异或值。若两点已经连通，就检查现有关系是否等于回答；否则按回答把两个集合合并。坐标最大到 $10^9$，字典只保存实际出现的 `l-1` 和 `r`。

### Python 知识

- 三个字典分别保存 `parent`、`size`、`parity`，无需先离散化成连续下标。
- 递归 `find` 在按大小合并后深度为 $O(\log m)$，并在回溯时同步压缩异或权。
- 输入中的 `word == b"odd"` 直接得到目标奇偶值 `True/False`，可参与异或运算。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(m\alpha(m))$，空间复杂度 $O(m)$。

### 总结

区间奇偶约束的本质是前缀异或点之间的关系，带权并查集负责维护并检查这些关系。
