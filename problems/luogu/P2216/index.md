---
oj: "luogu"
problem_id: "P2216"
title: "[HAOI2007] 理想的正方形"
description: "先横向、再纵向运行单调队列，在线性时间得到每个 n×n 方块的最大值和最小值。"
difficulty: "普及+/提高"
date: 2026-07-16 18:25
toc: true
tags: ["单调队列", "二维滑动窗口", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2216
---

[[TOC]]

### 题意

在矩阵所有固定边长正方形中，最小化内部最大值与最小值之差。

### 思路

先对每行做长度 `side` 的滑动最小值和最大值，得到所有横条结果；再对每个结果列做长度 `side` 的纵向滑动最值。第二遍得到的正好是每个正方形的整体最小值、最大值。

### Python 知识

- `deque` 保存候选下标，横向和纵向各扫描一次。
- 中间矩阵用 `array("i")` 保存，百万级 32 位值内存稳定。
- 分开保存横向最小、最大结果，第二遍只访问所需列。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(ab)$，空间复杂度 $O(ab)$。

### 总结

二维固定窗口最值可以拆成两次一维单调队列。
