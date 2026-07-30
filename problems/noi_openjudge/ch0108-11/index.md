---
oj: "noi_openjudge"
problem_id: "ch0108-11"
title: "图像旋转"
description: "按列从下到上读取原图，直接生成顺时针旋转 90 度后的图像。"
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
source: http://noi.openjudge.cn/ch0108/11/
---

[[TOC]]

### 题意

将 $n\times m$ 图像顺时针旋转 $90$ 度。

### 思路

旋转结果的每一行对应原图的一列，且该列要从下到上读取。外层枚举原列，内层从最后一行到第一行输出。

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

时间复杂度为 $O(nm)$，输入矩阵空间为 $O(nm)$。

### 总结

矩阵旋转可转化为明确的行列读取顺序，无需额外构造结果矩阵。
