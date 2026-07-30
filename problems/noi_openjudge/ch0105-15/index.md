---
oj: "noi_openjudge"
problem_id: "ch0105-15"
title: "银行利息"
description: "按复利公式计算最终金额，再用 int 截去小数部分。"
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
source: http://noi.openjudge.cn/ch0105/15/
---

[[TOC]]

### 题意

本金按年利率 $R$ 复利投资 $Y$ 年，输出最终金额的整数部分。

### 思路

每年增长因子为 $1+R/100$，最终金额是 $M(1+R/100)^Y$。题目要整数部分，Python 的 `int` 对正数直接截去小数部分。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

使用内建幂运算，额外空间复杂度为 $O(1)$。

### 总结

复利与单利不同，每一年都作用在上一年的本息和上，因此要使用乘方。
