---
oj: "noi_openjudge"
problem_id: "ch0104-04"
title: "奇偶ASCII值判断"
description: "用 ord 得到字符的 ASCII 码后判断其奇偶性。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/04/
---

[[TOC]]

### 题意

输入一个字符，若其 ASCII 码为奇数输出 `YES`，否则输出 `NO`。

### 思路

`ord(character)` 得到字符码点。题面范围是 ASCII，所以该码点就是 ASCII 值；再用 `% 2` 判断奇偶。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

字符与编码互转分别使用 `ord` 和 `chr`。
