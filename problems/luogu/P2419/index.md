---
oj: "luogu"
problem_id: "P2419"
title: "[USACO08JAN] Cow Contest S"
description: "用位集传递闭包统计每头牛已知强于和弱于的数量。"
difficulty: "普及"
date: 2026-07-17 03:00
toc: true
tags: ["传递闭包", "位运算", "偏序", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2419
---

[[TOC]]

### 题意

由比赛胜负关系判断有多少头牛的完整排名可以确定。

### 思路

胜者指向败者，位集 Warshall 求所有间接胜负。对牛 `i`，它能到达的数量加能够到达它的数量若为 `n-1`，说明与其他每头牛的强弱都已确定，排名唯一。

### Python 知识

- 一行可达集合编码成 Python 整数。
- `mask >> cow & 1` 检查其他行是否能到达该牛。
- 布尔值可直接参与整数求和。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

进行 `O(n^2)` 次位集 OR，空间 `O(n^2)` 位。

### 总结

排名可确定等价于该元素与所有其他元素都存在已知偏序关系。
