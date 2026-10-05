---
oj: "roj"
problem_id: "1285"
title: "最大上升子序列和"
description: "DP：f[i] 表示以 a[i] 结尾的最大上升子序列和，从前驱严格更小的位置转移，最后取全部 f[i] 的最大值。"
difficulty: "普及-"
date: 2026-09-30 03:14
updated: 2026-10-05 08:03
toc: true
tags: ["动态规划", "最长上升子序列", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1285
---

[[TOC]]

## 题目描述

给定长度为 $n$（$1 \le n \le 1000$）的整数序列，元素取值范围 $0 \sim 10000$。按原下标顺序选出严格递增的子序列，求所选元素之和的最大值。注意最长上升子序列的和不一定最大，例如 $(100,1,2,3)$ 的最大上升子序列和为 $100$。

## 思路

设 $f[i]$ 为以第 $i$ 个数结尾的最大上升子序列和。枚举 $i$ 前面的位置 $j$，若 $a_j < a_i$ 则可接上，$f[i] = \max(f[j] + a_i)$；若前驱为空则 $f[i] = a_i$。最终答案为所有 $f[i]$ 的最大值。

## 参考代码

@include-code(./main.cpp, cpp)
