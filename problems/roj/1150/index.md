---
oj: "roj"
problem_id: "1150"
title: "求正整数2和n之间的完全数"
description: "枚举 2~n 的每个数，利用因子成对性只试除到 √i 求真因子和，O(n√n) 找出区间内全部完全数。"
difficulty: "入门"
date: 2026-09-29 21:03
updated: 2026-10-05 03:32
toc: true
tags: ["数论", "枚举", "试除法"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1150
---

[[TOC]]

## 题目描述

求正整数 2 和 n 之间的完全数，一行一个按升序。完全数指真因子（含 1、不含自身）之和等于它本身的自然数，例如 $6 = 1 + 2 + 3$。输入一个整数 $n\ (n \leqslant 1000)$；输出一行一个数。样例输入 `7` 输出 `6`。

## 思路

对每个 $i \in [2, n]$，用试除法累加真因子之和：因子成对出现，只枚举 $d \in [2, \sqrt{i})$ 把 $d$ 与 $i/d$ 一起加，再单独处理完全平方数的 $\sqrt{i}$ 一次；和等于 $i$ 就输出。复杂度 $O(n\sqrt{n})$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)