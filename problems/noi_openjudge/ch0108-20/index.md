---
oj: "noi_openjudge"
problem_id: "ch0108-20"
title: "反反复复"
description: "先还原蛇形读取的行方向，再按列从上到下读取矩阵恢复原始信息。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/20/
---

[[TOC]]

### 题意

给定蛇形逐行读出的密文和列数，恢复原始按列从上到下填入的字符串。

### 思路

密文每 `column_count` 个字符是一行；偶数编号行在加密时从右向左读取，需要先反转回来。恢复所有正常行后，按列从左到右、每列从上到下读取，就是原始填入顺序。

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

设密文长度为 $L$，时间和额外空间复杂度均为 $O(L)$。

### 总结

蛇形编码的解码通常先还原每行方向，再按原填充方向遍历。
