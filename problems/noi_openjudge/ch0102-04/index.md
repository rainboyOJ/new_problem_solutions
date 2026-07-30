---
oj: "noi_openjudge"
problem_id: "ch0102-04"
title: "填空：类型转换1"
description: "由 32768 与 -32768 的转换结果判断 a 为 int、b 为 short。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["类型转换", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0102/04/
---

[[TOC]]

### 题意

判断两个 C/C++ 变量的类型：赋值后 `a` 输出 `32768`，`b` 输出 `-32768`。

### 思路

`32768` 超出了 16 位有符号 `short` 的最大值 $32767$，所以 `a` 必须是能保存它的 `int`，对应选项 `D`。把该位模式转为 16 位 `short` 后，最高位成为符号位，结果为 $-32768$，故 `b` 对应 `C`。

Python 整数没有固定 16 位溢出，这一题考查的是 C/C++ 转换规则，Python 程序直接输出判断结果。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

先检查值是否超出候选类型范围，再用补码解释截断后的位模式，就能判断这类整型转换题。
