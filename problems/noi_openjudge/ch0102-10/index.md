---
oj: "noi_openjudge"
problem_id: "ch0102-10"
title: "Hello, World!的大小"
description: "13 个可见字符加 C 字符串结尾的空字符，共占 14 个字节。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "类型转换", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0102/10/
---

[[TOC]]

### 题意

输出 C/C++ 字符串字面量 `"Hello, World!"` 的 `sizeof` 结果。

### 思路

可见字符串长度是 13，但 C 风格字符串还会在结尾存放一个 `\\0` 作为结束标记。因此字面量数组共有 $13 + 1 = 14$ 个 `char`，输出 `14`。

Python 字符串不以 C 的空字符结尾，`len("Hello, World!")` 只会得到 13；本题的目标是 C/C++ 的 `sizeof` 结论，Python 程序输出固定答案。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

`sizeof` 字符串字面量会计算末尾 `\\0`，而 `strlen` 和 Python 的 `len` 只统计可见字符。
