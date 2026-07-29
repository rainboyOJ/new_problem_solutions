---
oj: "leetcodecn"
problem_id: "number-of-islands"
title: "岛屿数量"
difficulty: "普及+/提高"
tags: [DFS, BFS, 网格, cpp, python]
description: "遇到未访问陆地就 DFS 淹没整块，计数加一。"
date: 2026-07-29 13:10
toc: true
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/number-of-islands/
---
[[TOC]]
### 题意
网格中 '1' 为陆地，找连通块数量。
### 思路
扫描网格，遇到 '1' 就 DFS/BFS 将整块淹没并计数。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
时间 O(mn)，空间 O(mn) 递归栈。
### 总结
淹没法是连通块计数的标准 DFS 做法。
