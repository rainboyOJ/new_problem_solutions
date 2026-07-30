---
oj: "noi_openjudge"
problem_id: "ch0112-04"
title: "最匹配的矩阵"
description: "枚举大矩阵中所有可放置位置，比较对应元素绝对差之和。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["枚举", "矩阵", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0112/04/
---

[[TOC]]

### 题意

在大矩阵中选择一个与给定小矩阵同尺寸的子矩阵，使对应元素差的绝对值和最小；并按左上角行、列优先打破平局。

### 思路

按行优先、列次优先枚举所有左上角位置，双层循环累加对应元素的绝对差。仅在严格更小时更新答案，因此相等时会自然保留先枚举到的行列更小的位置。最后按记录的位置切片输出。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O((m-r+1)(n-s+1)rs)$，空间复杂度为 $O(mn)$。

### 总结

枚举顺序与“平局选最小坐标”的规则一致时，更新条件只需使用严格小于。
