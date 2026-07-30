---
oj: "noi_openjudge"
problem_id: "ch0111-08"
title: "不重复地输出数"
description: "用集合去重后排序，输出严格递增的整数序列。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["排序", "集合", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0111/08/
---

[[TOC]]

### 题意

读入大量整数，按从小到大顺序输出每个不同整数一次。

### 思路

集合自动去重，`sorted(numbers)` 得到严格递增列表。最后使用 `print(*...)` 以单个空格分隔输出。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设不同整数有 $m$ 个，时间复杂度为 $O(n + m \log m)$，空间复杂度为 $O(m)$。

### 总结

当只关心不同元素的有序集合时，`set` 加 `sorted` 足够直接。
