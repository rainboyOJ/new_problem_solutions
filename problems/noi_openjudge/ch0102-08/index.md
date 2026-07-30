---
oj: "noi_openjudge"
problem_id: "ch0102-08"
title: "打印字符"
description: "使用 chr 把输入的 ASCII 整数编码转换为对应字符。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符", "类型转换", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0102/08/
---

[[TOC]]

### 题意

输入一个对应可见字符的 ASCII 码，输出该字符。

### 思路

先用 `int(input())` 把文本读成整数，再调用 `chr(ascii_code)`。`chr` 是 `ord` 的反向操作；题目保证编码落在可见 ASCII 范围，因此结果正是一个可输出字符。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

编码转字符用 `chr`，字符转编码用 `ord`。二者是一对常用的 Python 内建函数。
