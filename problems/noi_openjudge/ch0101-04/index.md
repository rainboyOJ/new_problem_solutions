---
oj: "noi_openjudge"
problem_id: "ch0101-04"
title: "输出保留3位小数的浮点数"
description: "先按单精度 float 舍入，再用 .3f 固定输出三位小数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["浮点数", "输出", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0101/04/
---

[[TOC]]

### 题意

读入一个单精度浮点数，按固定小数点格式输出，且小数点后恰好保留 3 位。

### 思路

`f"{value:.3f}"` 中的 `.3f` 表示固定小数点格式并保留 3 位，末尾的零也会保留。

Python 的 `float` 是双精度，而题目明确规定输入是单精度。代码先用 `struct.pack` 与 `struct.unpack` 完成一次 IEEE 754 单精度舍入，再格式化输出；这样靠近舍入边界的数据也和 C++ 的 `float` 一致。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

只读写一个数，时间复杂度为 $O(1)$，额外空间复杂度为 $O(1)$。

### 总结

`.3f` 解决的是输出位数；题面出现“单精度”时，还要留意 Python 双精度 `float` 与 C++ `float` 的存储精度不同。
