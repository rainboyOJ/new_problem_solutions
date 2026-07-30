---
oj: "noi_openjudge"
problem_id: "ch0107-12"
title: "加密的病历单"
description: "按加密步骤的逆序恢复大小写、顺序和字母位置，解密病历字符串。"
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
source: http://noi.openjudge.cn/ch0107/12/
---

[[TOC]]

### 题意

密文由“字母左移三位、整体逆序、大小写互换”得到，要求恢复原文。

### 思路

解密必须反向执行：先 `swapcase()`，再切片 `[::-1]` 逆序，最后对每个字母循环右移三位。循环位移通过把字母映射到 $0$ 到 $25$ 后取模实现。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(n)$。

### 总结

复合变换的逆操作顺序必须完全倒过来。
