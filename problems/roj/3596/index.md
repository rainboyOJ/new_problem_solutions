---
oj: "roj"
problem_id: "3596"
title: "[NOIP2012-普及] 摆花"
description: "以「前 i 种花摆 j 盆的方案数」为状态，转移是长度 a_i+1 的滑动窗口和：前缀和把单格压到 O(1)，一维滚动 O(n·m) 完成计数。"
difficulty: "普及-"
date: 2026-10-02 09:40
updated: 2026-10-07 13:50
toc: true
tags: ["动态规划", "多重背包", "前缀和", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "8005"
    reason: "B 的窗口和转移整行套用了 A 的前缀和消除求和：先对上一阶段整行做前缀和，再用 $S[j]-S[j-a_i-1]$ 一次减法代替逐项枚举，把 $O(a_i)$ 压成 $O(1)$"
common: []
recommend: []
source: https://roj.ac.cn/problem/3596
---

[[TOC]]

## 题目描述

有 $n$ 种花，第 $i$ 种最多摆 $a_i$ 盆。要把 $m$ 盆花摆成一排，要求同种花连续、不同种类按编号从小到大依次出现。求合法摆法总数，答案对 $1000007$ 取模。

**输入格式**：第一行 $n, m$；第二行 $n$ 个整数 $a_1 \dots a_n$。  
**输出格式**：一个整数，表示方案数对 $1000007$ 取模的结果。  
**样例输入**：`2 4 / 3 2`　**样例输出**：`2`

数据范围：$0 < n \leqslant 100,\ 0 < m \leqslant 100$。

## 思路

设 $f[j]$ 为前若干种花恰好摆 $j$ 盆的方案数。加入第 $i$ 种花时，$f[j]$ 等于上一阶段 $dp[j-a_i..j]$ 的滑动窗口和。用前缀和把单格求和压到 $O(1)$，一维滚动数组即可，总复杂度 $O(n \cdot m)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
