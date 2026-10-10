---
oj: "roj"
problem_id: "3521"
title: "[NOIP2003-普及] 栈"
description: "求 1~n 经栈操作得到的合法输出序列总数，即第 n 个卡特兰数，用 O(n) 递推计算。"
difficulty: "普及-"
date: 2026-10-02 05:05
updated: 2026-10-06 13:03
toc: true
tags: ["组合数学", "卡特兰数", "递推", "python"]
favorite: false
favorite_reason: ""
categories: ["组合数学"]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3521
---

[[TOC]]

## 题目描述

给定 $n$（$1\le n\le 18$），初始有操作数序列 $1,2,\dots,n$、空栈和空输出序列。每次可将操作数序列头端元素入栈，或将栈顶元素弹出到输出序列末尾。求最终能得到的不同输出序列总数。

样例 $n=3$ 时输出为 $5$。

## 思路

合法输出序列的总数即为第 $n$ 个卡特兰数。利用递推式 $C_0=1$，$C_k=C_{k-1}\cdot\dfrac{2(2k-1)}{k+1}$，$O(n)$ 递推即可得到答案。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
