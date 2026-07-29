---
oj: "leetcodecn"
problem_id: "rotate-image"
title: "旋转图像"
description: "先沿主对角线转置，再逐行反转；原地旋转 90 度顺时针，O(n²) O(1)。"
difficulty: "普及+/提高"
date: 2026-07-28 22:05
toc: true
tags: ["数组", "矩阵", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/rotate-image/
---

[[TOC]]

### 题意

n×n 矩阵顺时针旋转 90 度，原地修改。

### 思路

顺时针旋转 90° = 转置 + 每行反转。转置交换 `(i,j)` 和 `(j,i)`，然后每行反转即得顺时针旋转。也可用四元交换按层旋转。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(n²)，每个元素访问一次。
- 空间复杂度：O(1)。

### 总结

转置+反转是矩阵旋转的标准技巧。逆时针旋转 = 转置 + 每列反转。
