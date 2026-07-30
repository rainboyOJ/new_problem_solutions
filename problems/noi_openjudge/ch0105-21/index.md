---
oj: "noi_openjudge"
problem_id: "ch0105-21"
title: "角谷猜想"
description: "按奇偶规则迭代并逐行输出从初值到 1 的变换过程。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "循环", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/21/
---

[[TOC]]

### 题意

正整数为奇数时变为 $3n+1$，偶数时变为 $n/2$，逐行输出过程直到得到 1，最后输出 `End`。

### 思路

循环条件是 `number != 1`。每次先按奇偶计算 `next_number` 并按题面格式输出，再将当前数更新为它；输入本身为 1 时循环不执行，直接输出 `End`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设变换次数为 $t$，时间复杂度为 $O(t)$，额外空间复杂度为 $O(1)$。

### 总结

过程输出题要区分“计算前的当前状态”和“计算后的下一状态”，输出后再更新状态。
