---
oj: "shumeng"
problem_id: "CSP201512A"
title: "数位之和"
description: "反复取十进制末位并除以 10，累加所有数位。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "数位"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201512A
---

[[TOC]]

### 题意

求一个非负整数所有十进制数位的和。

### 思路

基准程序按字符串逐字符累加：

@include-code(./brute.cpp, cpp)

整数的 `n % 10` 是末位，`n / 10` 删除末位。不断重复并累加末位，直到整数变为 0。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设数位数为 $d$，时间复杂度为 $O(d)$，空间复杂度为 $O(1)$。

### 总结

取模和整除是十进制数位模拟的基本操作；输入为 0 时答案保持初值 0。
