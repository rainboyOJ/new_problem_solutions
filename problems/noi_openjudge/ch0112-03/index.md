---
oj: "noi_openjudge"
problem_id: "ch0112-03"
title: "甲流病人初筛"
description: "顺序筛选体温不低于 37.5 且咳嗽的病人，并统计人数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0112/03/
---

[[TOC]]

### 题意

筛选体温不低于 37.5 度且有咳嗽症状的病人，按输入顺序输出姓名和人数。

### 思路

逐行检查两个条件，满足时将姓名加入列表。列表本身保持输入顺序，最后逐行输出并输出长度。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

筛选题的输出顺序通常由顺序遍历自然保证。
