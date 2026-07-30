---
oj: "noi_openjudge"
problem_id: "ch0107-33"
title: "判断字符串是否为回文"
description: "比较原字符串与其切片逆序结果，判断是否为回文。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "回文", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/33/
---

[[TOC]]

### 题意

判断一个无空白字符串是否为回文。

### 思路

切片 `text[::-1]` 得到逆序字符串；两者相等当且仅当原串为回文。

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

时间和额外空间复杂度均为 $O(n)$。

### 总结

单次回文判断中，切片逆序比手写双指针更紧凑。
