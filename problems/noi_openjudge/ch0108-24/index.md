---
oj: "noi_openjudge"
problem_id: "ch0108-24"
title: "蛇形填充数组"
description: "按副对角线编号交替方向填充，构造 1 到 n 平方的蛇形方阵。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "模拟", "构造", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/24/
---

[[TOC]]

### 题意

用 $1$ 到 $n^2$ 沿左下到右上的各条斜线交替方向填充方阵。

### 思路

同一副对角线的坐标满足 `row + column = diagonal`。每条对角线先求合法行范围；奇数编号按行递增填充，偶数编号反向填充，方向自然交替。

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

填充和输出每格一次，时间和空间复杂度均为 $O(n^2)$。

### 总结

蛇形对角线填充可归结为“固定坐标和的斜线”与方向交替。
