---
oj: "roj"
problem_id: "3555"
title: "[NOIP2007-普及] Hanoi双塔问题"
description: "汉诺塔双塔版：同尺寸两盘看作整体，A_n = 2A_{n-1}+2，通项 2^{n+1}-2，高精度输出。"
difficulty: "普及-"
date: 2026-10-02 07:19
updated: 2026-10-06 13:51
toc: true
tags: ["递推", "数学", "高精度"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3555
---

[[TOC]]

## 题目描述

$A$、$B$、$C$ 三根柱子，$A$ 柱上叠着 $2n$ 个圆盘，共 $n$ 种尺寸，每种尺寸恰好两个相同且不加区分的圆盘。每次只能移动某柱最顶端的一个圆盘到另一柱顶，任何时刻三根柱都要保持上小下大。求把全部 $2n$ 个盘移到 $C$ 柱的最少移动次数 $A_n$。

输入一个正整数 $n$（$1 \le n \le 200$），输出 $A_n$。

样例输入 1：`1`，输出 `2`；样例输入 2：`2`，输出 `6`。

## 思路

把最大的 2 个盘看成整体：先花 $A_{n-1}$ 步把上面 $2(n-1)$ 个盘搬到 $B$，再各用 1 步把两个最大盘落到 $C$ 底，最后再花 $A_{n-1}$ 步把 $B$ 上的盘搬回 $C$，得 $A_n = 2A_{n-1} + 2$，$A_1 = 2$。展开递推得通项 $A_n = 2^{n+1} - 2$。$n = 200$ 时约有 61 位十进制，超出 64 位整数，需要手写高精度。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
