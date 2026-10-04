---
oj: "roj"
problem_id: "1172"
title: "求10000以内n的阶乘"
description: "n! 有 35660 位，必须高精度：数组一位存一个数字，每次乘 i 后统一进位。"
difficulty: "入门"
date: 2026-09-29 22:01
updated: 2026-10-05 04:18
toc: true
tags: ["高精度", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1172
---

[[TOC]]

## 题目描述

求 $n!$ 的精确值（约定 $0! = 1$），结果不含前导零。

**输入**：一行一个整数 $n$（$0 \leqslant n \leqslant 10000$）。

**输出**：一行，即 $n!$ 的值。

**样例输入**：`4`　**样例输出**：`24`

## 思路

$10000!$ 有 35660 位，64 位整数装不下，必须手写高精度：用数组 `a` 从低位到高位一位存一个十进制数字，`a[0]` 记位数。从 1 乘到 $n$，每次把现有每一位乘 $i$ 再统一进位即可，复杂度 $O(nD)$（$D$ 为结果位数）。

## 参考代码

@include-code(./main.cpp, cpp)
