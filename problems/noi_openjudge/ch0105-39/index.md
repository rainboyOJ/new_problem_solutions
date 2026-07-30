---
oj: "noi_openjudge"
problem_id: "ch0105-39"
title: "与7无关的数"
description: "枚举 1 至 n，排除 7 的倍数和含数字 7 的数后累加平方。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["枚举", "字符串", "整除", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/39/
---

[[TOC]]

### 题意

求不超过 $n$ 的所有“与 7 无关”的正整数的平方和。与 7 相关指能被 7 整除，或十进制表示中含有数字 `7`。

### 思路

枚举 $1$ 到 $n$。`number % 7 != 0` 判断是否不是 7 的倍数，`"7" not in str(number)` 判断数位中是否没有 7；两个条件都成立时累加平方。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设 $n$ 的十进制位数为 $d$，时间复杂度为 $O(nd)$，额外空间复杂度为 $O(d)$。

### 总结

数位存在性判断可直接转成字符串，逻辑比手动反复取余更紧凑。
