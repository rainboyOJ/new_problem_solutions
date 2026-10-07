---
oj: "roj"
problem_id: "1002"
title: "输出第二个整数"
description: "读入一行三个整数后原样输出第二个：scanf(\"%lld %lld %lld\") 后只取中间值。"
difficulty: "入门"
date: 2026-09-29 11:15
updated: 2026-10-04 22:07
toc: true
tags: ["输入输出", "cpp"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1002
---

[[TOC]]
## 题目描述

输入一行三个 32 位有符号整数（空格分隔），输出第二个。数据范围 $-2^{31}\le a,b,c\le 2^{31}-1$。

```
输入：123 456 789
输出：456
```
## 思路

用 `scanf("%lld %lld %lld", &a, &b, &c)` 读入三个整数到 `a,b,c`，再 `printf("%lld\n", b)` 输出第二个。
## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)