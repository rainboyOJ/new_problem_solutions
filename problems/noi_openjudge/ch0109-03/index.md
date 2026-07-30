---
oj: "noi_openjudge"
problem_id: "ch0109-03"
title: "不高兴的津津"
description: "遍历七天课程总时长，仅在出现更长时更新最不高兴的最早日期。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "最值", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0109/03/
---

[[TOC]]

### 题意

每天课程超过八小时会不高兴，输出课程总时长最大的最早一天；没有超过八小时则输出 $0$。

### 思路

初始最长时长设为 $8$。仅当新时长严格更大才更新日期，因此总时长并列时会保留更早的日期。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

固定七天，时间和额外空间复杂度均为 $O(1)$。

### 总结

需要保留首次最值时，更新条件使用严格比较。
## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)
