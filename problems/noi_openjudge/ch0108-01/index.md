---
oj: "noi_openjudge"
problem_id: "ch0108-01"
title: "矩阵交换行"
description: "读取 5x5 矩阵后直接交换两个列表行，再逐行输出。"
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
source: http://noi.openjudge.cn/ch0108/01/
---

[[TOC]]

### 题意

交换 $5\times5$ 矩阵中指定的两行并输出矩阵。

### 思路

矩阵的每一行可表示为一个列表，两个列表可用并行赋值直接交换。题目行号从 $1$ 开始，列表下标需减一。

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

Python 中交换两行不必逐元素交换，直接交换对应列表即可。
