---
oj: "noi_openjudge"
problem_id: "ch0104-06"
title: "判断是否为两位数"
description: "用闭区间 10<=n<=99 判断正整数是否为两位数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/06/
---

[[TOC]]

### 题意

判断正整数是否在两位数范围 $[10,99]$ 内，输出 `1` 或 `0`。

### 思路

Python 支持链式比较，`10 <= number <= 99` 同时表达上下界。布尔值转换为整数后，`True` 为 `1`，`False` 为 `0`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

区间判断优先写成链式比较，边界是否包含一眼可见。
