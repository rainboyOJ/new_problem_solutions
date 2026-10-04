---
oj: "roj"
problem_id: "1036"
title: "A×B问题"
description: "读入两个正整数，用 long long 存储并输出乘积。"
difficulty: "入门"
date: 2026-09-29 15:24
updated: 2026-10-04 23:06
toc: true
tags: ["输入输出", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1036
---

[[TOC]]

## 题目描述

输入两个正整数 $A$ 和 $B$（$1 \le A,B \le 50000$），输出 $A \times B$ 的值。

数据范围：$1 \le A,B \le 50000$，乘积最大 $2.5 \times 10^9$。

## 思路

直接用 `long long` 读入两个数并输出乘积，避免 `int` 溢出。

## 参考代码

@include-code(./main.cpp, cpp)
