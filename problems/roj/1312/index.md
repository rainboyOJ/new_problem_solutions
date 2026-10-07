---
oj: "roj"
problem_id: "1312"
title: "【例3.4】昆虫繁殖"
description: "按月的双序列线性递推：b[i]=y·a[i-x] 记每月产卵、a[i]=a[i-1]+b[i-2] 记两月后孵化，初值 a[1..x+2]=1，O(z) 求第 z+1 个月的成虫对数。"
difficulty: "入门"
date: 2026-09-30 04:35
updated: 2026-10-05 08:58
toc: true
tags: ["递推", "动态规划", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1312
---

[[TOC]]

## 题目描述

每对成虫过 $x$ 个月后每月产 $y$ 对卵，每对卵过两个月长成成虫，成虫不死；第 1 个月只有 1 对成虫。求第 $z+1$ 个月（即再过 $z$ 个月）的成虫对数。输入 $x$、$y$、$z$（$0 \le x \le 20$，$1 \le y \le 20$，$x \le z \le 50$），输出一个整数。样例输入 `1 2 8`，输出 `37`。

## 思路

设 $a_i$ 为第 $i$ 个月的成虫对数、$b_i$ 为第 $i$ 个月新产的卵对数。成虫不死且成熟满 $x$ 个月后每月一产，故 $b_i = y \cdot a_{i-x}$；卵要两个月才孵化，故 $a_i = a_{i-1} + b_{i-2}$，初值 $a_1 = \cdots = a_{x+2} = 1$，答案即 $a_{z+1}$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
