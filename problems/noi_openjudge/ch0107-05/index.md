---
oj: "noi_openjudge"
problem_id: "ch0107-05"
title: "输出亲朋字符串"
description: "把字符串视作循环序列，将每个字符与后继字符 ASCII 值之和转为新字符。"
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
source: http://noi.openjudge.cn/ch0107/05/
---

[[TOC]]

### 题意

构造亲朋字符串：每个位置输出当前字符与下一个字符 ASCII 值之和，最后一个字符与第一个配对。

### 思路

`text[1:] + text[:1]` 把首字符接到末尾，形成后继字符序列。两串 `zip` 后对每对字符取 `ord` 之和，再用 `chr` 转回字符。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(n)$。

### 总结

循环相邻关系可通过“去首后接首”的字符串构造直接表达。
