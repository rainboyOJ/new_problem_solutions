---
oj: "roj"
problem_id: "1454"
title: "「一本通 1.4 练习 4」山峰和山谷"
description: "8 邻接等权连通块洪泛，每块只记录外部邻居有无更矮/更高者：无更高即山峰，无更矮即山谷，O(n²)。"
difficulty: "普及"
date: 2026-09-30 11:45
updated: 2026-10-05 23:55
toc: true
tags: [广度优先搜索, 连通块, 网格图]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1454
---

[[TOC]]

## 题目描述

给定 $n\times n$ 的网格，每格有高度 $w_{ij}$，有公共顶点即相邻（8 邻接）。等高的 8 连通块，若周围格子都比它矮则为山峰，都比它高则为山谷；全图同高时整体既算山峰也算山谷。求山峰与山谷的数量。

**输入**：第一行 $n$（$2\le n\le1000$），随后 $n$ 行每行 $n$ 个整数 $w_{ij}$（$0\le w_{ij}\le10^9$）。**输出**：一行两个整数，山峰数与山谷数。样例：输入 `5 / 8 8 8 7 7 / 7 7 8 8 7 / 7 7 7 7 7 / 7 8 8 7 8 / 7 8 8 8 8`，输出 `2 1`。

## 思路

枚举每个未访问的格子，用 BFS 沿 8 个方向吞并所有同高的格子，得到一个等权连通块。洪泛时检查块内每格的 8 个邻居：出界忽略，同高则并入，更高或更矮分别记录 `has_higher` / `has_lower`；块外邻居必与块高不同，所以无更高即山峰、无更矮即山谷，两者可同时成立，全图同高的特例自然被覆盖。总复杂度 $O(n^2)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
