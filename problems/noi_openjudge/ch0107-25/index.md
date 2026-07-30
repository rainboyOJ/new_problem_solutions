---
oj: "noi_openjudge"
problem_id: "ch0107-25"
title: "最长最短单词"
description: "将逗号视作分隔符后切词，利用 max 与 min 的稳定性保留首次极值。"
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
source: http://noi.openjudge.cn/ch0107/25/
---

[[TOC]]

### 题意

句子以空格或逗号分隔单词，输出第一个最长单词和第一个最短单词。

### 思路

先把逗号替换为空格再切分。`max(words, key=len)` 与 `min(words, key=len)` 在并列时保留首次出现的元素，恰好符合题意。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，单词列表使用 $O(n)$ 空间。

### 总结

Python 的 `max` 和 `min` 对并列键值稳定，适合“第一个最值”问题。
