---
oj: "noi_openjudge"
problem_id: "ch0108-09"
title: "矩阵乘法"
description: "按矩阵乘法定义累加 A 的行和 B 的列的对应乘积，输出结果矩阵。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/09/
---

[[TOC]]

### 题意

计算 $n\times m$ 矩阵 $A$ 与 $m\times k$ 矩阵 $B$ 的乘积。

### 思路

结果的第 $i,j$ 项是 `A[i]` 与 $B$ 的第 $j$ 列对应元素乘积之和。外层枚举 $A$ 的行和结果列，内层枚举公共维度。

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

时间复杂度为 $O(nmk)$，输入矩阵空间为 $O(nm+mk)$。

### 总结

矩阵乘法不是对应相乘，而是“一行乘一列”的内积。
