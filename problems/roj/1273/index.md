---
oj: "roj"
problem_id: "1273"
title: "【例9.17】货币系统"
description: "完全背包方案计数：外层按面值分层保证不重不漏，内层金额正序枚举允许面值无限复用，f[m] 即组合方案数。"
difficulty: "普及-"
date: 2026-09-30 02:52
updated: 2026-10-05 07:44
toc: true
tags:
  - "DP"
  - "完全背包"
  - "计数DP"
favorite: false
favorite_reason: ""
categories:
  - "动态规划"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1273
---

[[TOC]]

## 题目描述

给定 $n$ 种面值（正整数，每种可无限使用），求恰好凑出总面值 $m$ 的方案数。两种方案不同当且仅当某种面值使用张数不同。

输入：第一行 $n,m$，接下来 $n$ 行每行一个面值。输出：一行方案数。

样例：$n=3,m=10$，面值 $\{1,2,5\}$，输出 $10$。

## 思路

完全背包计数。设 $f[j]$ 为凑出面值 $j$ 的方案数，$f[0]=1$。外层按面值分层去重，内层金额正序枚举使面值可无限复用：$f[j] \leftarrow f[j]+f[j-a_i]$。答案为 $f[m]$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
