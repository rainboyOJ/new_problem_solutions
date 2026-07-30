---
oj: "noi_openjudge"
problem_id: "ch0109-04"
title: "谁拿了最多奖学金"
description: "按五条奖学金规则累计每名学生奖金，同时维护最高奖金和总奖金。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "分类讨论", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0109/04/
---

[[TOC]]

### 题意

按五项条件计算每位学生奖金，输出奖金最多的最早学生、其奖金和全体奖金总和。

### 思路

对每位学生分别判断五条规则并累加奖金。只在奖金严格更大时更新最高记录，因此并列时自然保留先输入的学生。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

多条件累计题应把每项奖金的判断独立写出。
