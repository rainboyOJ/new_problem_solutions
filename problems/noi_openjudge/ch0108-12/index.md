---
oj: "noi_openjudge"
problem_id: "ch0108-12"
title: "变幻的矩阵"
description: "构造四种候选变换矩阵并依次与目标矩阵比较，输出匹配规则编号。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "模拟", "分类讨论", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/12/
---

[[TOC]]

### 题意

判断方阵经过顺时针、逆时针、中心对称、不变或其他哪种规则后得到目标矩阵。

### 思路

分别按下标关系构造顺时针、逆时针和中心对称矩阵。按照原题解的优先级先检查不变，再检查三种变换，未匹配则输出 $5$。

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

构造和比较常数个 $N\times N$ 矩阵，时间与空间复杂度均为 $O(N^2)$。

### 总结

固定数量的几何变换，直接构造候选结果再比较最清楚。
