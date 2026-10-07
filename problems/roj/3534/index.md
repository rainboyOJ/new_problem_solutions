---
oj: "roj"
problem_id: "3534"
title: "[NOIP2004-提高] 合唱队形"
description: "枚举峰：以它结尾的最长严格上升子序列 + 以它开头的最长严格下降子序列，峰被重复计算需减 1，答案为 N 减去最大单峰子序列长度。"
difficulty: "普及-"
date: 2026-10-02 05:52
updated: 2026-10-06 13:28
toc: true
tags: [动态规划, 线性DP, lis, python]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3534
---

[[TOC]]

## 题目描述

$N$ 位同学站成一排，删去若干人后使剩余身高满足先严格上升至峰、再严格下降。求最少出列人数。

输入：第一行整数 $N(2\le N\le100)$，第二行 $N$ 个整数 $T_i(130\le T_i\le230)$。输出：一个整数。

样例：输入 `8` 与 `186 186 150 200 160 130 197 220`，输出 `4`。

## 思路

枚举峰 $i$，以 $i$ 结尾的最长严格上升长度 $up_i$ 与以 $i$ 开头的最长严格下降长度 $down_i$ 拼接，峰被算两次需减 $1$；答案 $=N-\max_i(up_i+down_i-1)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
