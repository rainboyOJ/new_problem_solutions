---
oj: "roj"
problem_id: "1174"
title: "大整数乘法"
description: "200 位十进制大整数相乘，结果最多 400 位；按位拆十进制做 O(nm) 竖式乘，最后统一进位输出。"
difficulty: "入门"
date: 2026-09-29 22:02
updated: 2026-10-05 04:18
toc: true
tags: ["高精度", "入门", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1174
---

[[TOC]]

## 题目描述

求两个不超过 200 位的非负整数的积。输入两行，每行一个十进制非负整数（无前导 0）；输出一行乘积，无前导 0。样例：`12345678900 × 98765432100 = 1219326311126352690000`。

## 思路

两数都按十进制拆成各位存数组（低位在前），按 `c[i+j] += a[i]*b[j]` 双重循环累加，再从低位向高位统一进位、最后从最高位反向输出。共 `O(nm)` 次位乘，对 `n=m=200` 约 `4×10^4`，毫无压力。

## 参考代码

@include-code(./main.cpp, cpp)