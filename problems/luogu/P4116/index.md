---
oj: "luogu"
problem_id: "P4116"
title: "Qtree3"
description: "HLD 加线段树最小值，按根到节点顺序寻找路径上的第一个黑点。"
difficulty: "提高"
date: 2026-07-17 02:00
toc: true
tags: ["重链剖分", "线段树", "路径查询", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4116
---

[[TOC]]

### 题意

切换节点黑白颜色，查询根到给定节点路径上的第一个黑点。

### 思路

黑点叶子保存 dfn，白点保存无穷大。把路径拆成若干重链段后反转段列表，从根侧开始取区间最小 dfn；第一个非无穷结果就是答案。

### Python 知识

- `bytearray` 保存黑白状态，切换用异或。
- 迭代线段树区间最小值支持点更新和区间查询。
- `reversed(segments)` 保持查询方向与根到节点一致。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

每次操作 `O(log^2 n)`，空间 `O(n)`。

### 总结

路径上“第一个”元素要同时考虑拆段顺序和段内最小位置。
