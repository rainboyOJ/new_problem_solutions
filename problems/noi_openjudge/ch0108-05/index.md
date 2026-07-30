---
oj: "noi_openjudge"
problem_id: "ch0108-05"
title: "计算鞍点"
description: "逐行找唯一最大值，再判断它是否同时为所在列最小值来定位鞍点。"
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
source: http://noi.openjudge.cn/ch0108/05/
---


[[TOC]]

### 题意

寻找 $5\times5$ 矩阵中既是所在行最大值又是所在列最小值的鞍点。

### 思路

每行最多只有一个候选，即该行最大值。找到候选列后，检查它是否等于这一列的最小值；满足时立即输出。

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

矩阵规模固定，时间和额外空间复杂度均为 $O(1)$。

### 总结

行最大、列最小的复合条件可先缩小到每行唯一候选，再验证另一条件。
