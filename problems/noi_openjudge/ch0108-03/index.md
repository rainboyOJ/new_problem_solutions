---
oj: "noi_openjudge"
problem_id: "ch0108-03"
title: "计算矩阵边缘元素之和"
description: "读入矩阵时按行列边界判断，累加所有边缘元素且不重复计数。"
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
source: http://noi.openjudge.cn/ch0108/03/
---

[[TOC]]

### 题意

计算整数矩阵第一行、最后一行、第一列和最后一列元素之和。

### 思路

读取每个元素时判断其行或列是否位于边界。使用一个 `or` 条件，四个角也只会被累加一次。

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

时间复杂度为 $O(mn)$，除单行输入外额外空间复杂度为 $O(n)$。

### 总结

矩阵边界判断可以在读取阶段完成，无需保存整张矩阵。
