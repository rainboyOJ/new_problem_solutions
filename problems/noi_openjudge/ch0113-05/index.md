---
oj: "noi_openjudge"
problem_id: "ch0113-05"
title: "素数回文数的个数"
description: "枚举区间整数，同时检查试除素性和字符串回文性。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["素数", "回文", "枚举", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0113/05/
---

[[TOC]]

### 题意

统计 11 到 $n$ 之间既是素数又是回文数的整数个数。

### 思路

范围小于 1000，直接枚举即可。试除到平方根判断素数，`text == text[::-1]` 判断回文，同时满足就计数。

### 代码

## Python代码

@include-code(./main.py, python)

### 复杂度

时间复杂度为 $O(n\sqrt n)$，空间复杂度为 $O(1)$。

### 总结

小范围题中，清晰的直接枚举通常优于复杂预处理。
