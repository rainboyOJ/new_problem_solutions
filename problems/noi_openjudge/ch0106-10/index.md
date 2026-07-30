---
oj: "noi_openjudge"
problem_id: "ch0106-10"
title: "大整数加法"
description: "利用 Python 任意精度整数直接完成不超过 200 位的非负整数加法。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["高精度", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0106/10/
---

[[TOC]]

### 题意

求两个不超过 $200$ 位的非负整数之和，并去除结果前导零。

### 思路

Python 的 `int` 是任意精度整数，读入时转换为 `int` 后直接相加即可。再次输出整数时，前导零会自然消失；全为零时会正确输出 `0`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设较长数字有 $d$ 位，时间复杂度为 $O(d)$，额外空间复杂度为 $O(d)$。

### 总结

Python OJ 中遇到普通十进制大整数时，应优先确认内置 `int` 是否已足够。
