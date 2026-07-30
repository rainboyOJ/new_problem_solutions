---
oj: "noi_openjudge"
problem_id: "ch0108-07"
title: "矩阵归零消减序列和"
description: "每轮先记录第二行第二列，再行列归零并删除第二行第二列。"
difficulty: "普及/提高-"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/07/
---

[[TOC]]

### 题意

反复对方阵行归零、列归零并删除第二行第二列，输出每次消减前该位置的值，最后输出 $1\times1$ 阶段的 `0`。

### 思路

当前矩阵大小大于 $1$ 时，先记录 `matrix[1][1]`。之后每行减行最小值、每列减列最小值，再通过切片删除下标为 $1$ 的行和列。行列归零不会改变非负性。

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

各阶段总工作量为 $O(n^3)$，矩阵空间复杂度为 $O(n^2)$。

### 总结

多阶段矩阵模拟必须严格区分“记录值”“归零”和“删除”的执行顺序。
