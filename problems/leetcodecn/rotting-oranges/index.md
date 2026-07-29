---
oj: "leetcodecn"
problem_id: "rotting-oranges"
title: "腐烂的橘子"
difficulty: "普及+/提高"
tags: [BFS, 多源, 网格, cpp, python]
description: "所有腐烂橘子同时入队，多源 BFS 按层传播，统计分钟。"
date: 2026-07-29 13:10
toc: true
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/rotting-oranges/
---
[[TOC]]
### 题意
每分钟腐烂橘子会使相邻新鲜橘子腐烂，求全部腐烂所需最少分钟。
### 思路
多源 BFS：所有初始腐烂橘子入队，按层传播。每层表示一分钟，统计新鲜橘子数。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
时间 O(mn)，空间 O(mn)。
### 总结
多源 BFS 适合同时从多个起点开始扩散的问题。
