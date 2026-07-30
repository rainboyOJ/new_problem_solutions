---
oj: "noi_openjudge"
problem_id: "ch0101-08"
title: "字符三角形"
description: "用字符串重复构造长度为 1、3、5 的三行字符三角形。"
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
source: http://noi.openjudge.cn/ch0101/08/
---

[[TOC]]

### 题意

给定一个字符，输出高为 3、底边长度为 5 的等腰字符三角形。三行字符数依次为 1、3、5，前导空格数依次为 2、1、0。

### 思路

Python 中 `character * count` 会把一个字符串重复 `count` 次，因此每行都可以直接写出“前导空格 + 重复后的字符”。

本题的图案大小固定，逐行 `print` 比循环更直接，也更容易检查每一行的空格数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

这里保留原有的 C++ 参考实现。

@include-code(./main.cpp, cpp)

### 复杂度

输出字符数固定，时间复杂度为 $O(1)$，额外空间复杂度为 $O(1)$。

### 总结

字符画题先列出每一行的“前导空格数”和“字符数”。Python 的字符串乘法适合把重复字符表达得清楚。
