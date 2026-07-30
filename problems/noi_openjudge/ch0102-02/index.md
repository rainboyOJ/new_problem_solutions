---
oj: "noi_openjudge"
problem_id: "ch0102-02"
title: "浮点型数据类型存储空间大小"
description: "输出 OpenJudge C/C++ 环境中 float 与 double 的固定字节数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0102/02/
---

[[TOC]]

### 题意

输出题目指定 C/C++ 环境中 `float` 和 `double` 分别占用的字节数。

### 思路

目标环境中单精度 `float` 占 4 字节，双精度 `double` 占 8 字节。Python 只有一个内建 `float` 类型，通常对应双精度；它的对象内存布局不能用来回答 C/C++ 的 `sizeof` 题，所以直接输出题目要求的平台常量。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

`float` 与 `double` 的主要区别是精度和存储空间。本题的答案来自固定评测平台，不能拿 Python 对象大小替代。
