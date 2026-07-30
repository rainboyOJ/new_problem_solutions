---
oj: "noi_openjudge"
problem_id: "ch0104-10"
title: "有一门课不及格的学生"
description: "两个不及格布尔值不同，恰好一门课不及格。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/10/
---

[[TOC]]

### 题意

判断语文和数学是否恰好只有一门不及格。

### 思路

令两个布尔值分别表示 `chinese < 60`、`math < 60`。它们一真一假时才满足题意，Python 中布尔值的 `!=` 恰好表示这种异或关系。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

“恰好一个”是异或条件；对布尔值可直接写 `condition1 != condition2`。
