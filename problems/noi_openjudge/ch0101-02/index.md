---
oj: "noi_openjudge"
problem_id: "ch0101-02"
title: "输出第二个整数"
description: "按空白切分三个整数后，直接输出中间的第二个数。"
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
source: http://noi.openjudge.cn/ch0101/02/
---

[[TOC]]

### 题意

一行给出三个 32 位有符号整数，输出中间读入的第二个整数。

### 思路

这一题不需要计算。`input().split()` 按空白分隔读入三个字段，`map(int, ...)` 把它们转成整数。解包时把两侧无须使用的值写成 `_`，第二个值保存为 `second` 并输出。

这样仍然是“按整数读入”：例如输入中的 `0007` 会按整数规则输出为 `7`，而不是原样保留前导零。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

固定读入三个数，时间复杂度为 $O(1)$，额外空间复杂度为 $O(1)$。

### 总结

当一行中字段数量固定时，解包能让“第几个数”直接对应到变量位置。未使用的字段用 `_` 表示即可。
