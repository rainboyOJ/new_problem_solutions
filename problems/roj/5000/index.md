---
oj: "roj"
problem_id: "5000"
title: "整数划分"
description: "把划分数写成 (剩余和, 下一段上限) 的记忆化递归：枚举首段后把上限收紧为它，非增约定天然去重，指数枚举降到 O(n³)。"
difficulty: "入门"
date: 2026-10-02 15:16
updated: 2026-10-06 16:34
toc: true
tags: ["递归", "记忆化搜索", "整数划分", "计数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/5000
---

[[TOC]]

## 题目描述

给定正整数 $n$，求把 $n$ 写成若干正整数之和的方案数（加数顺序不同视为同一划分，$n$ 本身也算一种），即划分数 $p(n)$。

## 思路

完全背包计数：令 $dp[j]$ 为凑出 $j$ 的划分数，枚举每个可用加数 $i=1\dots n$ 做 $dp[j] \mathrel{+}= dp[j-i]$，恰好消除顺序重复，$O(n^2)$ 得 $p(n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
