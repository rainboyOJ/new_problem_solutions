---
oj: "noi_openjudge"
problem_id: "ch0101-09"
title: "字符菱形"
description: "按 1、3、5、3、1 的字符数和对应前导空格直接输出菱形。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["输出", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0101/09/
---

[[TOC]]

### 题意

给定一个字符，输出对角线长度为 5 的菱形。五行字符数依次为 1、3、5、3、1，前导空格数依次为 2、1、0、1、2。

### 思路

菱形可以看成字符三角形先扩张再收缩。由于只有固定 5 行，直接按行输出最清楚：使用 `character * 3` 和 `character * 5` 产生对应宽度，再用 f-string 放入前导空格。

每行末尾不拼接额外空格，避免字符画题常见的格式错误。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

输出规模固定，时间复杂度为 $O(1)$，额外空间复杂度为 $O(1)$。

### 总结

对于固定大小字符画，先写出每行的空格数和字符数，再逐行输出，比用复杂循环更不容易出错。
