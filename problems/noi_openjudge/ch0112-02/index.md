---
oj: "noi_openjudge"
problem_id: "ch0112-02"
title: "短信计费"
description: "每条短信用向上取整计算计费条数，再累加并换算为元。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0112/02/
---

[[TOC]]

### 题意

每 70 个字或不足 70 个字计一条短信，统计总资费。

### 思路

长度为 `length` 的短信需计费 `(length + 69) // 70` 条，这是正整数除法的向上取整公式。累计条数后乘以 0.1 元并固定输出一位小数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，空间复杂度为 $O(1)$。

### 总结

正整数向上取整除法可记作 `(a + b - 1) // b`。
