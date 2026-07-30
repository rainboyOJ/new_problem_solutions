---
oj: "noi_openjudge"
problem_id: "ch0105-27"
title: "级数求和"
description: "从第一项开始累加调和级数，直到和严格大于给定整数 K。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["循环", "模拟", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/27/
---

[[TOC]]

### 题意

求最小的正整数 $n$，使得

$$
1 + \frac{1}{2} + \cdots + \frac{1}{n} > K.
$$

### 思路

从第 $1$ 项开始逐项累加。变量 `term` 表示当前加入的是第几项，`total` 表示已经得到的级数和。

循环条件必须写为 `total <= threshold`：题目要求的是严格大于 $K$，当和恰好等于 $K$ 时还必须继续加入下一项。循环结束时的 `term` 就是最小答案。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设答案为 $n$，循环执行 $n$ 次，时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

处理“最小位置使条件成立”时，先写清结束条件是否包含等号，能避免典型的边界错误。
