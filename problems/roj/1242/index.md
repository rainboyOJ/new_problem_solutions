---
oj: "roj"
problem_id: "1242"
title: "网线主管"
description: "长度乘 100 化成厘米整数后，切出段数随切割长度单调不增，在 [0, max+1] 上开区间二分最大可行长度，O(n log V) 求解，无解由 lo=0 哨兵统一输出 0.00。"
difficulty: "普及-"
date: 2026-09-30 01:19
updated: 2026-10-05 06:30
toc: true
tags: ["二分答案", "二分", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1242
---

[[TOC]]

## 题目描述

给定 $n$ 条网线长度（米，两位小数），把它们切成 $k$ 条等长网线（剩余丢弃），求能切出的最大长度，输出两位小数；若连 $1$ 厘米都切不出则输出 `0.00`。

## 思路

长度乘 $100$ 化为厘米整数，使答案落在整数网格上。设 $f(L)=\sum_i \lfloor a_i/L \rfloor$，$L$ 越大段数越少，可行域是前缀，故在 $[0,\max a_i+1]$ 上开区间二分最大满足 $f(L)\ge k$ 的 $L$；`lo=0` 作为无解哨兵直接输出 `0.00`。

## 参考代码

@include-code(./main.cpp, cpp)
