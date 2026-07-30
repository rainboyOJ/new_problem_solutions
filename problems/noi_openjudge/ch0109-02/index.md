---
oj: "noi_openjudge"
problem_id: "ch0109-02"
title: "输出最高分数的学生姓名"
description: "逐个读取分数和姓名，仅在分数更高时更新最高分学生。"
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
source: http://noi.openjudge.cn/ch0109/02/
---

[[TOC]]

### 题意

输出唯一最高分学生的姓名。

### 思路

维护当前最高分和对应姓名。逐条读入时只有发现更高分数才更新，最终姓名即答案。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

只需最优记录时可边读取边更新，无需保存全部学生。
## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)
