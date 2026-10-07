---
oj: "roj"
problem_id: "1408"
title: "素数回文数的个数"
description: "从 11 到 n 枚举每个整数，先判回文再判素数，统计两条件都满足的个数。"
difficulty: "入门"
date: 2026-09-30 09:04
updated: 2026-10-05 23:11
toc: true
tags:
  - 质数判定
  - 枚举
  - 回文数
favorite: false
favorite_reason: ""
categories:
  - 数学
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1408
---

[[TOC]]

## 题目描述

求 $11$ 到 $n$（包括 $n$）之间，既是素数又是回文数的整数有多少个。$11<n<1000$。

## 思路

数据范围很小，直接枚举 $[11,n]$ 中的每个整数；先判断是否为回文数，再判断是否为素数，两个条件都满足则计数加一。把回文判定放在前面，多数数会被快速短路掉。

## 参考代码

@include-code(./main.cpp, cpp)
