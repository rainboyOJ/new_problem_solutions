---
oj: "noi_openjudge"
problem_id: "ch0106-09"
title: "向量点积计算"
description: "用 zip 配对两个向量对应分量，累加乘积得到点积。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数组", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0106/09/
---

[[TOC]]

### 题意

求两个 $n$ 维向量的点积 $\sum a_i b_i$。

### 思路

`zip(first, second)` 依次配对两个向量的对应分量，生成器表达式计算每对乘积，`sum` 完成累加。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，除输入序列外额外空间复杂度为 $O(1)$。

### 总结

对应位置的乘积和是 `zip` 与生成器表达式的典型组合。
