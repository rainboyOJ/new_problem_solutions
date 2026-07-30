---
oj: "noi_openjudge"
problem_id: "ch0108-06"
title: "图像相似度"
description: "保存第一幅图像后逐位置比较第二幅图像，统计相同像素比例。"
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
source: http://noi.openjudge.cn/ch0108/06/
---

[[TOC]]

### 题意

计算两幅相同大小黑白图像的相同像素比例并保留两位小数。

### 思路

先保存第一幅图像。读入第二幅图像的每一行时，用 `zip` 逐位置比较并累计相同数，最后除以总像素数并乘 $100$。

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

时间复杂度为 $O(mn)$，保存第一幅图像使用 $O(mn)$ 空间。

### 总结

两组同形矩阵的逐位置比较可沿输入同步完成。
