---
oj: "noi_openjudge"
problem_id: "ch0112-10"
title: "素数对"
description: "用埃氏筛标记不超过 n 的素数，再枚举相差为 2 的素数对。"
difficulty: "普及-"
date: 2026-07-30 23:01
updated: 2026-10-06 02:35
toc: true
tags: ["素数", "筛法", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre:
  - oj: "roj"
    problem_id: "1151"
    reason: "B 的 Python 解法直接复用 A 教的埃氏筛（平方起标记合数）先打出素数表，再叠加枚举差为 2 的素数对"
common: []
recommend: []
source: http://noi.openjudge.cn/ch0112/10/
---

[[TOC]]

### 题意

输出两个数都不超过 $n$、且差为 2 的全部素数对；不存在则输出 `empty`。

### 思路

埃氏筛先标记所有素数：从每个尚为素数的 `number` 开始，将其平方起的倍数标为合数。随后枚举 `p` 并检查 `p + 2` 是否也为素数即可。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

筛法时间复杂度为 $O(n \log\log n)$，空间复杂度为 $O(n)$。

### 总结

需要一次判断大量小范围整数是否为素数时，筛法比逐个试除更合适。
