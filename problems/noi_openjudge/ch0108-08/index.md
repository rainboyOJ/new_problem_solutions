---
oj: "noi_openjudge"
problem_id: "ch0108-08"
title: "矩阵加法"
description: "逐行配对两个同形矩阵的元素，计算并输出对应位置的和。"
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
source: http://noi.openjudge.cn/ch0108/08/
---

[[TOC]]

### 题意

计算两个同为 $n\times m$ 的矩阵逐元素之和。

### 思路

保存第一个矩阵后，读取第二个矩阵的每行并与对应行 `zip`，对每对元素相加后立刻输出。

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

时间复杂度为 $O(nm)$，保存第一个矩阵使用 $O(nm)$ 空间。

### 总结

同形矩阵运算的核心是对应位置配对。
