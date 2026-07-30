---
oj: "noi_openjudge"
problem_id: "ch0108-23"
title: "二维数组回形遍历"
description: "维护上下左右四条边界，按上右下左顺序逐层输出矩阵元素。"
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
source: http://noi.openjudge.cn/ch0108/23/
---

[[TOC]]

### 题意

从左上角开始顺时针向内回形遍历矩阵。

### 思路

维护未遍历区域的 `top`、`bottom`、`left`、`right`。依次走上边、右边、下边、左边，再整体收缩四条边界；单行或单列时跳过会重复输出的边。

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

螺旋遍历的关键是每圈结束后同步收缩四条边界。
