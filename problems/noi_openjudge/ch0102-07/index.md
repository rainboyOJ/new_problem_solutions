---
oj: "noi_openjudge"
problem_id: "ch0102-07"
title: "打印ASCII码"
description: "使用 ord 把一个可见 ASCII 字符转换为对应的十进制编码。"
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
source: http://noi.openjudge.cn/ch0102/07/
---

[[TOC]]

### 题意

输入一个非空的可见 ASCII 字符，输出它的十进制 ASCII 码。

### 思路

`input()` 读入一个字符串。题目保证只有一个可见字符，因此 `ord(character)` 可以直接取得它的 Unicode 码点；对 ASCII 范围内的字符，这个码点就是题目所说的 ASCII 码。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

字符转编码用 `ord`。题目限定 ASCII 时，Python 的 Unicode 码点与 ASCII 值相同。
