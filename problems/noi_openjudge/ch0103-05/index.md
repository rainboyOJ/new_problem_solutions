---
oj: "noi_openjudge"
problem_id: "ch0103-05"
title: "计算分数的浮点数值"
description: "使用真除法计算 a/b，并以 .9f 输出九位小数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0103/05/
---

[[TOC]]

### 题意

把两个整数视为分子和非零分母，输出分数的小数值，保留 9 位小数。

### 思路

Python 的 `/` 总是进行真除法，结果为浮点数。f-string 的 `.9f` 同时完成四舍五入和末尾补零。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

需要固定小数位时使用 `.nf`，不要依赖浮点数的默认输出。
