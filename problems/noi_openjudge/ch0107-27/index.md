---
oj: "noi_openjudge"
problem_id: "ch0107-27"
title: "单词翻转"
description: "用正则逐段匹配非空白单词并逆序，保留原句中所有空格。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "正则", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/27/
---

[[TOC]]

### 题意

逐个反转句子中的单词，单词之间的空格必须与原句一致。

### 思路

正则 `\S+` 只匹配连续的非空白字符。`re.sub` 仅替换这些单词片段为其逆序，未匹配的空格会原样保留。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间和输出空间复杂度均为 $O(n)$。

### 总结

既要转换单词又要保留分隔符时，按匹配片段替换很合适。
