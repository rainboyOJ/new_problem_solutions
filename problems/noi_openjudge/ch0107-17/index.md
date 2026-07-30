---
oj: "noi_openjudge"
problem_id: "ch0107-17"
title: "字符串判等"
description: "删除空格并统一转小写后，比较两行字符串是否相等。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "比较", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/17/
---

[[TOC]]

### 题意

判断两行只含字母和空格的字符串在忽略大小写与空格后是否相等。

### 思路

每行先用 `replace(" ", "")` 删除空格，再调用 `lower()`，比较规范化后的两个结果。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设总输入长度为 $n$，时间和额外空间复杂度均为 $O(n)$。

### 总结

多个“忽略规则”可依次规范化，再做一次普通相等比较。
