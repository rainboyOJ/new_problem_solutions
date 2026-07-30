---
oj: "noi_openjudge"
problem_id: "ch0103-11"
title: "计算浮点数相除的余数"
description: "用 a-int(a/b)*b 按题目定义求正浮点数除法余数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["浮点数", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0103/11/
---

[[TOC]]

### 题意

对两个正浮点数求余数 $r$，满足 $a=kb+r$ 且 $0\leqslant r<b$。

### 思路

先取 $k=\operatorname{int}(a/b)$，因为 $a,b$ 都为正，`int` 就是向下截断。余数为 `a - k * b`。题目要求末尾不补零，`g` 格式会按需要输出有效数字。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

浮点余数可从定义式构造；本题输入为正数，避免了负数取整方向的歧义。
