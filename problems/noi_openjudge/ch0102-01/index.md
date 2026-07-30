---
oj: "noi_openjudge"
problem_id: "ch0102-01"
title: "整型数据类型存储空间大小"
description: "输出 OpenJudge C/C++ 环境中 int 与 short 的固定字节数。"
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
source: http://noi.openjudge.cn/ch0102/01/
---

[[TOC]]

### 题意

输出题目指定的 C/C++ 评测环境中 `int` 与 `short` 的存储空间大小。

### 思路

这不是查询 Python 对象大小的题。`sys.getsizeof` 会包含 Python 对象的运行时开销，和 C/C++ 的 `sizeof` 没有可比性。根据题目所在平台，`int` 为 4 字节、`short` 为 2 字节，直接输出这两个固定值。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

语言数据类型的大小由实现决定；在这道 OJ 题中，目标平台已经固定，Python 解法应输出该平台的结论。
