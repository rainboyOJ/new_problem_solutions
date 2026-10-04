---
oj: "roj"
problem_id: "1151"
title: "素数个数"
description: "用埃拉托斯特尼筛法在 O(n log log n) 时间内统计 [2, n] 中的素数个数。"
difficulty: "入门"
date: 2026-09-29 21:02
updated: 2026-10-05 03:32
toc: true
tags: ["数论", "素数", "筛法"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1151
---

[[TOC]]

## 题目描述

求 $2 \sim n$（$2 \leqslant n \leqslant 50000$）中素数的个数。输入一行整数 $n$，输出素数个数。样例输入 `10`，对应输出 `4`。

## 思路

埃拉托斯特尼筛：从小到大枚举素数 $p$，把 $p^2, p^2+p, \dots$ 全部标记为合数。筛完后 $[2, n]$ 中未被标记的数就是素数，统计个数即可。

## 参考代码

@include-code(./main.cpp, cpp)
