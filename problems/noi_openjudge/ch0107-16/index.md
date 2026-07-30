---
oj: "noi_openjudge"
problem_id: "ch0107-16"
title: "忽略大小写的字符串比较"
description: "将两行字符串统一转小写后，按字典序直接比较大小。"
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
source: http://noi.openjudge.cn/ch0107/16/
---

[[TOC]]

### 题意

忽略字母大小写，比较两行字符串的字典序并输出 `<`、`>` 或 `=`。

### 思路

先对两串调用 `lower()` 消除大小写差异，Python 的字符串比较会按字典序完成逐字符比较。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设较长字符串长度为 $n$，时间复杂度为 $O(n)$，额外空间复杂度为 $O(n)$。

### 总结

忽略大小写的比较先做统一规范化，再复用普通字符串比较。
