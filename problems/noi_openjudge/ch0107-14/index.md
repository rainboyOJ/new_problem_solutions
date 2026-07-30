---
oj: "noi_openjudge"
problem_id: "ch0107-14"
title: "大小写字母互换"
description: "调用字符串 swapcase 逐字符互换大写与小写字母。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/14/
---

[[TOC]]

### 题意

将字符串中的大写字母替换为小写、小写替换为大写，其他字符不变。

### 思路

`swapcase()` 一次完成大小写互换，非字母字符保持原样。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和输出空间均为 $O(n)$。

### 总结

互换大小写与单向转换不同，应使用 `swapcase`。
