---
oj: "noi_openjudge"
problem_id: "ch0106-01"
title: "与指定数字相同的数的个数"
description: "读取整数序列后用列表 count 统计指定数字的出现次数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数组", "计数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0106/01/
---

[[TOC]]

### 题意

统计长度为 $N$ 的整数序列中，指定整数 $m$ 出现的次数。

### 思路

读入序列后，列表的 `count(target)` 直接返回目标值出现次数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(N)$，存储序列使用 $O(N)$ 空间。

### 总结

Python 列表的 `count` 适合小规模的单值频次统计。
