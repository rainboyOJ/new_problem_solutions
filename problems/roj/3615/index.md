---
oj: "roj"
problem_id: "3615"
title: "[NOIP2014]比例简化"
description: "枚举分子、分母均不超过 L 的既约分数，取不小于 A/B 且差最小者。"
difficulty: "普及"
date: 2026-10-02 10:41
updated: 2026-10-06 15:14
toc: true
tags: ["枚举", "数论", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3615
---

[[TOC]]

## 题目描述

输入三个正整数 $A,B,L$，在 $1 \le A',B' \le L$、$\gcd(A',B')=1$、$A'/B' \ge A/B$ 的约束下，找使 $A'/B' - A/B$ 最小的 $(A',B')$。输出 $A'$、$B'$。数据范围 $L \le 100$。

样例输入：`1498 902 10`，样例输出：`5 3`。

## 思路

枚举 $1 \le A',B' \le L$ 的每一对既约分数，用交叉相乘 $A' \cdot B \ge A \cdot B'$ 判断不小于原比例；误差比较也用交叉相乘，避免浮点；取差最小者，并列时按字典序取最小。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
