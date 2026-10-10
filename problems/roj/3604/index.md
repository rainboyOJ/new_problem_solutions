---
oj: "roj"
problem_id: "3604"
title: "[NOIP2013-普及]计数问题"
description: "数位统计：把 n 按每个数位切成高位/当前位/低位三段，用乘法原理一次性算出每位上 x 的出现次数，再对 0 做前导零修正，复杂度 O(log n)。"
difficulty: "普及-"
date: 2026-10-02 10:05
updated: 2026-10-06 15:07
toc: true
tags: ["数位统计", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3604
---

[[TOC]]

## 题目描述

试计算在区间 $1$ 到 $n$ 的所有整数中，数字 $x$（$0 \leqslant x \leqslant 9$）共出现了多少次。注意统计的是所有出现位置：例如在 $1$ 到 $11$ 中，即在 $1,2,\dots,11$ 中，数字 $1$ 出现在 $1$、$10$ 以及 $11$ 的两个数位上，共 $4$ 次。

输入格式：一行两个整数 $n, x$，用一个空格隔开。输出格式：一行一个整数，表示 $x$ 出现的次数。

输入样例#1：`11 1`，输出样例#1：`4`。

数据范围：$1 \leqslant n \leqslant 1{,}000{,}000$，$0 \leqslant x \leqslant 9$。

## 思路

数位统计：$1 \sim n$ 中 $x$ 的总次数等于它在每个数位上出现次数之和。对每个权重 $p$，把 $n$ 切成高位 $high$、当前位 $cur$、低位 $low$ 三段：当前位取 $0 \dots x-1$ 贡献 $high \times p$，$cur > x$ 再加 $p$，$cur = x$ 再加 $low + 1$。$x = 0$ 时前缀全 0 的数并不存在，每层要减去 $p$ 做前导零修正。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
