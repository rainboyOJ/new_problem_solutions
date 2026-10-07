---
oj: "roj"
problem_id: "1530"
title: "「一本通 3.7 练习 2」Ant Trip"
description: "并查集维护无向图连通块，统计每个含边连通块中奇度顶点的数量，计算最少一笔画覆盖数。"
difficulty: "普及"
date: 2026-09-30 16:31
updated: 2026-10-06 00:36
toc: true
tags:
  - "图论"
  - "并查集"
  - "欧拉图"
favorite: false
favorite_reason: ""
categories:
  - "图论"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1530
---

[[TOC]]

## 题目描述

给定无向图的 $N$ 个点和 $M$ 条边（无重边、无自环），多组数据用空行隔开。每组数据第一行两个整数 $N,M$，接下来 $M$ 行每行两个整数 $a,b$ 表示一条边。求最少几笔能把所有边画一遍，每笔不能离开纸且边不重复。孤立点无需遍历。

## 思路


含边连通块各自独立。若某连通块有 $k$ 个奇度顶点，则 $k=0$ 时一笔（欧拉回路），否则至少且恰好需要 $\frac{k}{2}$ 笔。用并查集维护连通块，统计每个点的度数和每个含边连通块的奇度点数即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
