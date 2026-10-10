---
oj: "roj"
problem_id: "1627"
title: "「一本通 6.3 例 3」最大公约数"
description: "辗转相除法求千位大整数的 gcd：手写高精度大整数取模，C++ 实现欧几里得算法。"
difficulty: "普及-"
date: 2026-09-30 22:54
updated: 2026-10-06 01:24
toc: true
tags: ["数论", "gcd", "辗转相除法", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1627
---

[[TOC]]

## 题目描述

给出两个正整数 $A,B$（$1 \le A,B \le 10^{3000}$），求它们的最大公约数。

输入共两行，每行一个正整数；输出一行一个整数表示答案。

## 思路

利用欧几里得算法 $\gcd(a,b)=\gcd(b,a\bmod b)$，每次把问题规模缩小，直到 $b=0$ 时 $a$ 即为答案。由于 $A,B$ 可达 $10^{3000}$，需要手写高精度大整数对大整数的取模运算，其余步骤与普通辗转相除法相同。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
