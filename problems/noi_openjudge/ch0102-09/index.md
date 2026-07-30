---
oj: "noi_openjudge"
problem_id: "ch0102-09"
title: "整型与布尔型的转换"
description: "用 bool 判断整数是否非零，再转成 int 输出 0 或 1。"
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
source: http://noi.openjudge.cn/ch0102/09/
---

[[TOC]]

### 题意

把一个整数转换为布尔值，再转换回整数，输出最终结果。

### 思路

整数转布尔值时，`0` 为假，任何非零整数为真。Python 用 `bool(number)` 完成这一步；再用 `int(...)` 把 `False`、`True` 分别转为 `0`、`1`，恰好对应 C/C++ 的结果。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

`int(bool(x))` 是把“是否非零”直接规范化成 `0` 或 `1` 的清晰写法。
