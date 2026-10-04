---
oj: "roj"
problem_id: "1041"
title: "奇偶数判断"
description: "奇偶性就是二进制最低位：n & 1 直接读出这一位，条件表达式一步映射到 odd/even，常数时间。"
difficulty: "入门"
date: 2026-09-29 15:47
updated: 2026-10-04 23:13
toc: true
tags: ["入门", "数学", "位运算", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1041
---

[[TOC]]

## 题目描述

给定一个正整数 $n$，判断它是奇数还是偶数；奇数输出 `odd`，偶数输出 `even`。一行输入一个大于零的正整数 $n$，一行输出对应结果。

样例输入 `5`，输出 `odd`。

## 思路

奇偶性只由 $n$ 的最低一位决定，二进制视角下就是 $n \bmod 2 = n \,\&\, 1$；为 `1` 输出 `odd`，为 `0` 输出 `even`，常数时间。

## 参考代码

@include-code(./main.cpp, cpp)