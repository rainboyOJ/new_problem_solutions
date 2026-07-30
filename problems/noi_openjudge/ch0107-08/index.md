---
oj: "noi_openjudge"
problem_id: "ch0107-08"
title: "字符替换"
description: "调用字符串 replace 将目标字符的全部出现替换为指定字符。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/08/
---

[[TOC]]

### 题意

把字符串中指定字符的所有出现替换成另一个字符。

### 思路

`text.replace(old, new)` 返回替换全部出现后的新字符串，正好对应题意。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和输出空间均为 $O(n)$。

### 总结

全量字面替换使用 `replace` 即可，无需手写循环。
