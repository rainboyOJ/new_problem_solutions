---
oj: "noi_openjudge"
problem_id: "ch0107-28"
title: "单词倒排"
description: "切分单词列表并整体 reversed，再用单个空格连接输出。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "数组", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/28/
---

[[TOC]]

### 题意

将由单个空格分隔的英文单词顺序完全倒排。

### 思路

`split()` 得到单词列表，`reversed` 反向遍历，`join` 负责重新插入单个空格。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间和输出空间复杂度均为 $O(n)$。

### 总结

单词顺序倒排与单词内部字符反转是两种不同操作。
