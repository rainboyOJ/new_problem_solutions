---
oj: "noi_openjudge"
problem_id: "ch0110-10"
title: "单词排序"
description: "按空白切分单词，用 set 去重后按 Python 字符串字典序排序。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["排序", "字符串", "集合", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0110/10/
---

[[TOC]]

### 题意

输入一行由一个或多个空格分隔的单词，区分大小写，去重后按字典序逐行输出。

### 思路

`split()` 会把连续空白都视为分隔符，正好适合本题。先用 `set` 去重，再对集合调用 `sorted`。Python 字符串默认按字典序比较，并区分大小写。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设不同单词数为 $m$，时间复杂度为 $O(n + m \log m)$，空间复杂度为 $O(m)$。

### 总结

`split`、`set`、`sorted` 依次对应切分、去重、排序三个独立步骤。
