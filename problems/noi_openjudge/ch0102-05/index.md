---
oj: "noi_openjudge"
problem_id: "ch0102-05"
title: "填空：类型转换2"
description: "由第九位小数能否保留判断 a 为 double、b 为 float。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["浮点数", "类型转换", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0102/05/
---

[[TOC]]

### 题意

根据赋值前后 `1.000000001` 的第九位小数是否还存在，判断两个 C/C++ 变量的类型。

### 思路

`a` 输出时仍保留 `1.000000001`，需要双精度 `double`，对应选项 `F`。赋值给 `b` 后输出为 `1.000000000`，说明单精度 `float` 的有效精度不足以区分这一微小差异，故 `b` 对应 `E`。

Python 的 `float` 通常就是双精度，不能用它直接演示 C++ 单精度丢失；本题要求的是类型选项，直接输出 `F E`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

浮点赋值可能因精度不同而改变值。观察变化发生在赋值前还是赋值后，可以反推出两个变量的精度。
