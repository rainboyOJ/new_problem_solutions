---
oj: "noi_openjudge"
problem_id: "ch0108-04"
title: "错误探测"
description: "统计奇数和的行列；零个则 OK，恰各一个则是唯一需翻转的位置。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "模拟", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/04/
---

[[TOC]]

### 题意

判断 $0/1$ 方阵每行每列的 $1$ 数量是否为偶数，或能否只翻转一个元素修复。

### 思路

翻转一个格子只会改变它所在行和列的奇偶性。因此没有奇数和行列时为 `OK`；恰好一条奇数和行、恰好一条奇数和列时，交点就是修复位置；其余为 `Corrupt`。

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

时间复杂度为 $O(n^2)$，矩阵空间复杂度为 $O(n^2)$。

### 总结

先分析一次操作影响哪些不变量，可避免枚举所有翻转位置。
