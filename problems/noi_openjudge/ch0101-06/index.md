---
oj: "noi_openjudge"
problem_id: "ch0101-06"
title: "空格分隔输出"
description: "按行读取字符和三类数值，并用 .6f 统一控制两个浮点数的小数位。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["输入输出", "浮点数", "输出", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0101/06/
---

[[TOC]]

### 题意

输入依次占四行：一个字符、一个整数、一个单精度浮点数和一个双精度浮点数。按原顺序输出，相邻字段一个空格，两个浮点数都保留 6 位小数。

### 思路

四行数据类型不同，逐行调用 `input()` 最直观：字符保留字符串，整数用 `int` 转换，浮点数用 `float` 转换。第三行题面规定为单精度，先通过 `struct` 做单精度舍入；第四行保持 Python 的双精度即可。

最后在一个 f-string 中写出各字段，并为两个浮点数使用 `.6f`。这样空格位置、小数点和补零都由同一条格式串控制。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

固定读写四个字段，时间复杂度为 $O(1)$，额外空间复杂度为 $O(1)$。

### 总结

混合输入时先按题面保留每一行的类型，再集中在 f-string 中规定输出格式；不要依赖普通 `print` 的浮点数默认表示。
