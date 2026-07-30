---
oj: "noi_openjudge"
problem_id: "ch0108-02"
title: "同行列对角线的格子"
description: "从目标格沿四个方向定位对角线起点，依次生成同行、列和两条对角线。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "模拟", "坐标", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/02/
---

[[TOC]]

### 题意

在 $N\times N$ 棋盘上输出与给定格同行、同列和同两条对角线的格子坐标。

### 思路

同行和同列直接枚举。主对角线先向左上移动到边界，再按 $(+1,+1)$ 前进；副对角线先向左下移动到边界，再按 $(-1,+1)$ 前进。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

<!-- 原解析未提供复杂度说明时，后续人工补充。 -->

### 总结

<!-- 保留原解析内容，不额外编造结论。 -->
## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

四条线各至多 $N$ 个格子，时间复杂度为 $O(N)$，额外空间复杂度为 $O(1)$。

### 总结

对角线输出先找规定方向的边界起点，便能保证题目要求的顺序。
