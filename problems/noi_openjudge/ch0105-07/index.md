---
oj: "noi_openjudge"
problem_id: "ch0105-07"
title: "奥运奖牌计数"
description: "逐日累计金银铜牌数，最后输出三类总数和总奖牌数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["循环", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/07/
---

[[TOC]]

### 题意

读入每天的金、银、铜牌数量，输出三类总数与总奖牌数。

### 思路

维护三个累计变量。每读入一行就分别相加，循环结束后总数为三个累计值之和。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

多字段统计时，让每个字段拥有独立累计器，最后再组合派生结果。
