---
oj: "noi_openjudge"
problem_id: "ch0107-13"
title: "将字符串中的小写字母转换成大写字母"
description: "调用字符串 upper 将所有小写字母统一转换为大写字母。"
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
source: http://noi.openjudge.cn/ch0107/13/
---

[[TOC]]

### 题意

将一行字符串中的所有小写字母转换为大写，其他字符不变。

### 思路

`upper()` 返回转换后的新字符串，直接符合题意。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和输出空间均为 $O(n)$。

### 总结

统一大小写优先使用字符串内置方法。
