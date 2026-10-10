---
oj: "roj"
problem_id: "1078"
title: "求分数序列和"
description: "维护当前项分母 p、分子 q，每轮累加 q/p 后把 (p,q) 更新为 (q,p+q)，迭代 n 次并保留 4 位小数。"
difficulty: "入门"
date: 2026-09-29 17:43
updated: 2026-10-05 00:20
toc: true
tags: ["入门", "递推", "数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1078
---

[[TOC]]

## 题目描述

分数序列满足 $q_1=2$，$p_1=1$，$q_{i+1}=q_i+p_i$，$p_{i+1}=q_i$。给定 $n\ (n\le 30)$，求前 $n$ 项 $\frac{q_i}{p_i}$ 之和，保留 4 位小数（输入一行 $n$，输出一行浮点数）。

样例输入 `2`，样例输出 `3.5000`。

## 思路

只需维护当前项的分母 $p$、分子 $q$：每轮先累加 $q/p$，再用临时变量把 $(p,q)$ 更新为 $(q,\,p+q)$，迭代 $n$ 次即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
