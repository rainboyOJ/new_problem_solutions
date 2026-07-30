---
oj: "noi_openjudge"
problem_id: "ch0107-24"
title: "单词的长度"
description: "按空白切分单词后计算长度，并用逗号连接所有长度。"
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
source: http://noi.openjudge.cn/ch0107/24/
---

[[TOC]]

### 题意

计算一行单词序列中每个单词的长度，结果以逗号分隔。

### 思路

标点未被空格隔开时属于同一个单词，所以只需 `split()`，再对每个单词调用 `len`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间和输出空间复杂度均为 $O(n)$。

### 总结

题目以空格定义单词时，不应额外把标点拆开。
