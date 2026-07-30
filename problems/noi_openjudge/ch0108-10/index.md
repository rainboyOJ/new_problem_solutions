---
oj: "noi_openjudge"
problem_id: "ch0108-10"
title: "矩阵转置"
description: "用 zip 解包矩阵行并按列组合，直接输出转置矩阵。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "数组", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/10/
---

[[TOC]]

### 题意

输出 $n\times m$ 矩阵的转置，即将行和列互换。

### 思路

`zip(*matrix)` 将所有行解包并按相同列下标组合，每个得到的元组就是转置矩阵的一行。

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

时间复杂度为 $O(nm)$，矩阵输入空间为 $O(nm)$。

### 总结

`zip(*matrix)` 是规则二维列表转置的简洁 Python 写法。
