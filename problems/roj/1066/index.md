---
oj: "roj"
problem_id: "1066"
title: "满足条件的数累加"
description: "区间 [m, n] 内的 17 的倍数构成公差 17 的等差数列，定位首末项后 O(1) 求和。"
difficulty: "入门"
date: 2026-07-05 21:47
updated: 2026-10-04 23:57
toc: true
tags: ["数论", "等差数列", "入门"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1066"
---

[[TOC]]

## 题目描述

给定两个正整数 $m,n$（$0<m<n<1000$），求区间 $[m,n]$ 内所有能被 $17$ 整除的数之和。输入一行两个整数 $m,n$，用一个空格隔开；输出一行，表示累加的结果。

样例输入 `50 85`，样例输出 `204`（$51+68+85$）。

## 思路

区间内的 17 的倍数构成公差为 17 的等差数列：首项取 $\ge m$ 的最小 17 的倍数，末项取 $\le n$ 的最大 17 的倍数，项数 $k=(last-first)/17+1$，答案为首末项平均乘项数。若首项大于末项，说明区间内无 17 的倍数，输出 0。

## 参考代码

@include-code(./main.cpp, cpp)
