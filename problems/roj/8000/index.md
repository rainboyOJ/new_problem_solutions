---
oj: "roj"
problem_id: "8000"
title: "平数"
description: "统计正数之和 P 与负数绝对值之和 N，两条下界不等式相加得答案 max(P,N)，配对构造恰好达到该下界。"
difficulty: "普及-"
date: 2026-10-02 16:22
updated: 2026-10-06 16:42
toc: true
tags: ["入门", "数学", "贪心", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/8000
---

[[TOC]]

## 题目描述

给定 $n$ 个整数 $a_1, \dots, a_n$。每次操作可任选其一：任选一个数加 1 或减 1；或任选两个不同下标 $i \neq j$，让其中一个加 1、另一个减 1。两类操作各算一次，求把所有数同时变成 0 所需的最少操作次数。

输入格式：第一行整数 $n$，第二行 $n$ 个整数。数据范围：$n \le 10^5$，$|a_i| \le 10^5$。输出格式：一行一个整数。样例输入 `5` 与 `1 2 -4 -1 8`，样例输出 `11`。

## 思路

记正数之和为 $P$、负数绝对值之和为 $N$：单个操作不改总和，成对操作只有"正挪给负"每次减少绝对值和 2，两条下界不等式 $x \ge |P-N|$ 与 $x+2y \ge P+N$ 相加得 $x+y \ge \max(P,N)$。按"先配对 $\min(P,N)$ 次、再单个操作清掉剩余 $|P-N|$ 次"构造恰好达到该下界，所以答案就是 $\max(P, N)$。一遍扫描统计 $P$、$N$ 即可，和最大可达 $10^{10}$ 要用 `long long`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
