---
oj: "noi_openjudge"
problem_id: "ch0107-01"
title: "统计数字字符个数"
description: "遍历整行字符串，用 isdigit 统计其中数字字符的数量。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "计数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/01/
---

[[TOC]]

### 题意

统计一行字符串中数字字符的个数。

### 思路

对每个字符调用 `isdigit()`；布尔值可以直接求和，真值贡献 $1$。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设字符串长度为 $n$，时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

字符分类统计可直接配合生成器表达式和 `sum`。
