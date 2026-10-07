---
oj: "roj"
problem_id: "1293"
title: "买书"
description: "完全背包计数：f[j] 表示凑成 j 元方案数，f[0]=1，按 10/20/50/100 正序滚动 f[j]+=f[j-price]；n=0 输出 0。"
difficulty: "入门"
date: 2026-09-30 03:41
updated: 2026-10-05 08:17
toc: true
tags: [动态规划, 背包问题, 完全背包, 计数DP]
favorite: false
favorite_reason: ""
categories: [动态规划]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1293
---

[[TOC]]

## 题目描述

小明有 n 元全部用来买书，书价为 10、20、50、100 元，每种可买多本，求恰好花完 n 元的方案数。输入一个整数 n（0 ≤ n ≤ 1000），输出方案种数；n=0 时按题目约定输出 0。样例：输入 20，输出 2；输入 15 或 0，输出 0。

## 思路

把买书方案看成完全背包计数：f[j] 表示凑成 j 元的方案数，f[0]=1，按 10/20/50/100 四种书价正序滚动 f[j] += f[j-price]。n=0 输出 0，否则输出 f[n]。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
