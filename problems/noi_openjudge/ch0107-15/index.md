---
oj: "noi_openjudge"
problem_id: "ch0107-15"
title: "整理药名"
description: "首字符单独转大写，其余字符统一转小写，规范化药品名称。"
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
source: http://noi.openjudge.cn/ch0107/15/
---

[[TOC]]

### 题意

将每个药名整理为首字符若为字母则大写，其余字母小写的形式。

### 思路

把第一个字符和后缀分开：`name[0].upper()` 处理首字符，`name[1:].lower()` 处理其余字符。首字符为数字或连字符时 `upper()` 不改变它。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设所有药名总长度为 $n$，时间和输出空间复杂度均为 $O(n)$。

### 总结

格式化首字符时，先分割首字符和剩余部分比复杂条件判断更直接。
