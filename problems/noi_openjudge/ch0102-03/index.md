---
oj: "noi_openjudge"
problem_id: "ch0102-03"
title: "其他基本数据类型存储空间大小"
description: "输出 OpenJudge C/C++ 环境中 bool 与 char 的固定字节数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0102/03/
---

[[TOC]]

### 题意

输出指定 C/C++ 环境中 `bool` 与 `char` 的存储空间大小。

### 思路

在本题的目标环境中，`bool` 和 `char` 都占 1 字节，因此直接输出 `1 1`。Python 的 `bool` 继承自 `int`，而字符是长度为 1 的 `str`；两者都不是 C/C++ 基本类型，不能通过 Python 的内存大小推导答案。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

跨语言学习时要分清“同名概念”和“同一种内存布局”：本题考查的是指定 C/C++ 平台，而不是 Python 运行时。
