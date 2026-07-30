---
oj: "noi_openjudge"
problem_id: "ch0112-05"
title: "统计单词数"
description: "统一转小写后按空格切分文章，统计完整单词匹配及首个位置。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0112/05/
---

[[TOC]]

### 题意

不区分大小写统计一个完整单词在文章中出现的次数和第一次出现的字符位置。

### 思路

先将目标词和文章统一转小写。文章只含字母和空格，使用 `split(" ")` 能逐个检查完整单词；同时累计每段长度和一个分隔空格，即可得到每个单词的起始下标。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(L)$，$L$ 为文章长度；空间复杂度为 $O(L)$。

### 总结

完整匹配应以单词为单位比较，而不是直接做子串查找。
