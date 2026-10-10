---
oj: "roj"
problem_id: "3606"
title: "[NOIP2013-普及]小朋友的数字"
description: "前缀最大子段和（Kadane 滚动值）+ 分数的前缀最大值 g，一遍 O(n) 扫描求所有人的分数最大值，按符号取模输出。"
difficulty: "普及-"
date: 2026-10-02 10:18
updated: 2026-10-06 15:07
toc: true
tags: ["最大子段和", "Kadane", "递推", "前缀最大值", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3606
---

[[TOC]]

## 题目描述

有 $n$ 个小朋友排成一列，每人手上有整数 $a_i$（可正可负）。特征值 $d_i$ 为前 $i$ 人中连续非空子段和的最大值；分数 $s_1=d_1$，$s_i\ (i\ge2)$ 为前面所有人中 $s_j+d_j$ 的最大值。求 $\max s_i$，保持符号并将绝对值对 $p$ 取模后输出。

数据范围：$1\le n\le10^6$，$1\le p\le10^9$，$|a_i|\le10^9$。

## 思路

特征值是前缀最大子段和，用 Kadane 滚动 `end_here` 并维护历史最大 `trait`。分数需要前面所有人 `score+trait` 的最大值，再用一个滚动变量 `g` 维护。全程四个标量，$O(n)$ 时间、$O(1)$ 额外空间。注意负数输出保持符号。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
