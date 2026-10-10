---
oj: "roj"
problem_id: "1096"
title: "数字统计"
description: "用前缀函数 F(x) 的递推求区间 [L,R] 中数字 2 的出现次数。"
difficulty: "入门"
date: 2026-09-29 18:40
updated: 2026-10-05 01:00
toc: true
tags: ["数位", "计数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1096
---

[[TOC]]

## 题目描述

统计区间 $[L,R]$ 内所有整数中数字 `2` 出现的次数。
输入一行两个正整数 $L,R$；输出一行一个整数表示次数。
样例输入：`2 22`，样例输出：`6`。

## 思路

把区间和写成前缀函数之差 $F(R)-F(L-1)$。设 $x=10q+r$，按个位分块得 $F(x)=10F(q-1)+q+(r+1)c(q)+[r\ge2]$，其中 $c(q)$ 为 $q$ 中数字 `2` 的个数。递归深度为位数，用 map 记忆化。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
