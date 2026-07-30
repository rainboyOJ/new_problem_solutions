---
oj: "noi_openjudge"
problem_id: "ch0107-21"
title: "单词替换"
description: "按单词切分句子，逐词比较并替换，再以空格重新连接。"
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
source: http://noi.openjudge.cn/ch0107/21/
---

[[TOC]]

### 题意

将句子中所有与指定单词完全相同的单词替换为新单词。

### 思路

按空格切分为单词，生成新单词序列后用空格连接。只对完整单词做相等比较，不会误替换单词内部的子串。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设句子长度为 $n$，时间和输出空间复杂度均为 $O(n)$。

### 总结

按单词替换应先切词，再比较完整词。
