---
oj: "noi_openjudge"
problem_id: "ch0108-21"
title: "二维数组右上左下遍历"
description: "按对角线编号确定顶端或右端起点，再沿左下方向输出全部元素。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "模拟", "遍历", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/21/
---

[[TOC]]

### 题意

从左上向右下逐条对角线遍历矩阵，每条对角线沿左下方向输出。

### 思路

第 $d$ 条对角线的起点在首行或最右列。确定起点后反复执行“行加一、列减一”，直到出界。

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

每个元素输出一次，时间复杂度为 $O(rc)$，矩阵空间为 $O(rc)$。

### 总结

对角线遍历可用“对角线编号 + 固定步长”统一实现。
