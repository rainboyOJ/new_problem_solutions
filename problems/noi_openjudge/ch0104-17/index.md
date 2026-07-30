---
oj: "noi_openjudge"
problem_id: "ch0104-17"
title: "判断闰年"
description: "按 4、100、400 和题设 3200 的整除规则判断闰年。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/17/
---

[[TOC]]

### 题意

按题设公历规则判断年份是否是闰年，输出 `Y` 或 `N`。

### 思路

普通规则是“能被 4 整除且不能被 100 整除，或能被 400 整除”。题面额外规定 3200 的倍数不是闰年，因此最后再加 `year % 3200 != 0`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

闰年题的难点在例外规则；用带括号的布尔表达式把优先级写清楚。
