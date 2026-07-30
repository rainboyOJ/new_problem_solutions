---
oj: "noi_openjudge"
problem_id: "ch0103-03"
title: "计算(a+b)/c的值"
description: "先求 a+b，再按 C/C++ 规则向零截断整数商。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "类型转换", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0103/03/
---

[[TOC]]

### 题意

计算整数表达式 $(a+b)/c$，除法为整除。

### 思路

C/C++ 整数除法向零截断，而 Python 的 `//` 对负数向下取整，例如 `-3 // 2` 为 `-2`。先对绝对值整除，再根据符号决定正负，就能得到跨语言一致的向零商。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

涉及负数整除时，不能想当然地把 C++ `/` 写成 Python `//`。
