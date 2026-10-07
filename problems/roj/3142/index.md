---
oj: "roj"
problem_id: "3142"
title: "「自然数拆分Lunatic版」 自然数拆分"
description: "完全背包计数：f[j] 表示用不大于当前上限的加数拆出 j 的方案数，正序枚举加数可重复，答案 f[N] 减 1。"
difficulty: "普及"
date: 2026-10-01 20:22
updated: 2026-10-06 02:35
toc: true
tags: ["动态规划", "完全背包问题"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
common: []
recommend: []
source: https://roj.ac.cn/problem/3142
---

[[TOC]]

## 题目描述

给定自然数 $N$，把它拆成若干正整数之和，方案不考虑顺序、加数可重复，且至少拆成两个数。输入一个整数 $N$，输出方案数对 $2147483648$ 取模的结果。$1 \le N \le 4000$。

样例输入 `7`，样例输出 `14`。

## 思路

把加数 $i$ 看成体积为 $i$ 的无限物品，背包容量为 $N$，统计恰好装满的方案数，即完全背包计数；一维数组正序更新 $f[j] += f[j-i]$，最后 $f[N]-1$ 去掉单加数方案 $N=N$。

## 参考代码

@include-code(./main.cpp, cpp)
