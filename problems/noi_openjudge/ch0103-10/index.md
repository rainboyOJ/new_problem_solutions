---
oj: "noi_openjudge"
problem_id: "ch0103-10"
title: "计算并联电阻的阻值"
description: "将并联公式化为 r1*r2/(r1+r2) 并保留两位小数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0103/10/
---

[[TOC]]

### 题意

输入两个电阻，输出它们并联后的阻值，保留 2 位小数。

### 思路

原式为 $R=1/(1/r_1+1/r_2)$。通分后得到 $R=r_1r_2/(r_1+r_2)$，代码使用后者，除法更少且表达清晰。用 `.2f` 输出。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

代数变形能把分式公式变成更直接的实现，前提是分母条件仍由题目保证。
