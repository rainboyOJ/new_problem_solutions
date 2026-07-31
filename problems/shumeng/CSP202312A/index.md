---
oj: "shumeng"
problem_id: "CSP202312A"
title: "仓库规划"
description: "按仓库编号从小到大枚举候选上级，选择第一个在所有编码维度都严格更大的仓库。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["枚举", "模拟"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202312A
---

[[TOC]]

### 题意

每个仓库有一个 $m$ 维整数位置编码。仓库 $j$ 可以作为仓库 $i$ 的上级，当且仅当 $j$ 的每一维编码都严格大于 $i$；如果有多个候选，选择编号最小的一个，否则输出 $0$。

### 思路

先看直接枚举所有候选仓库的暴力做法：

@include-code(./brute.cpp, cpp)

对于每个仓库 $i$，按照编号 $1,2,\ldots,n$ 检查候选仓库 $j$。只要发现某个维度满足 `code[j][k] <= code[i][k]`，就可以判定 $j$ 不合格；所有维度都严格大于时立即记录并停止枚举。由于枚举顺序就是编号递增，找到的第一个候选必然是编号最小的上级。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

最坏情况下每个仓库都要检查全部仓库和全部维度，时间复杂度为 $O(n^2m)$，空间复杂度为 $O(nm)$。

### 总结

题目只要求编号最小的可行候选，不需要比较候选之间的“优劣”。按编号顺序扫描并在第一个满足条件的位置停止，就同时完成了可行性判断和最小编号选择。
