---
oj: "noi_openjudge"
problem_id: "ch0107-23"
title: "过滤多余的空格"
description: "使用 split 去除连续空格，再以单个空格 join 重建句子。"
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
source: http://noi.openjudge.cn/ch0107/23/
---

[[TOC]]

### 题意

将句子中连续的多个空格压缩为一个空格。

### 思路

无参数 `split()` 会把连续空白视为一个分隔符，得到单词列表；`" ".join(...)` 用单个空格重新连接。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间和输出空间复杂度均为 $O(n)$。

### 总结

压缩分隔符的常用写法是 `" ".join(text.split())`。
