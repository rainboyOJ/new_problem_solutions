---
oj: "noi_openjudge"
problem_id: "ch0109-06"
title: "笨小猴"
description: "统计出现字符频率，判断最大最小频次之差是否为质数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "计数", "质数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0109/06/
---

[[TOC]]

### 题意

若单词字符最高频与最低频的差是质数，输出 `Lucky Word` 和该差。

### 思路

`Counter` 统计频率，取值集合的最大最小值相减。质数需至少为 $2$，再试除到平方根。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

<!-- 原解析未提供复杂度说明时，后续人工补充。 -->

### 总结

<!-- 保留原解析内容，不额外编造结论。 -->
## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，计数空间为 $O(26)$。

### 总结

频次差为 $0$ 或 $1$ 时都不是质数。
