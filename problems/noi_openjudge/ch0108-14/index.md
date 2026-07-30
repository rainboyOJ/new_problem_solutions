---
oj: "noi_openjudge"
problem_id: "ch0108-14"
title: "扫雷游戏地雷数计算"
description: "对每个非雷格检查八个合法邻居，统计其中星号数量并输出。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/14/
---

[[TOC]]

### 题意

根据雷区中 `*` 的位置，输出每个非雷格周围八个方向的地雷数。

### 思路

枚举八个方向，并在访问前判断邻居坐标仍在矩阵内。雷格原样输出，非雷格输出命中 `*` 的数量。

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

每格检查固定八个方向，时间复杂度为 $O(nm)$，额外空间为 $O(1)$（不含输入）。

### 总结

八方向网格题可把方向向量固定为一个元组后复用。
