---
oj: "roj"
problem_id: "1071"
title: "菲波那契数"
description: "菲波那契递推的水表题：两个变量滚动递推 k-2 次即得第 k 项，时间 O(k)、空间 O(1)。"
difficulty: "入门"
date: 2026-09-29 17:20
updated: 2026-10-05 00:10
toc: true
tags: ["递推", "循环", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1071
---

[[TOC]]

## 题目描述

菲波那契数列是指这样的数列：数列的第一个和第二个数都为 1，接下来每个数都等于前面 2 个数之和。给出一个正整数 k，要求菲波那契数列中第 k 个数是多少。

输入一行，包含一个正整数 k（1 ≤ k ≤ 46）。

输出一行，包含一个正整数，表示菲波那契数列中第 k 个数的大小。

样例：k = 19 时输出 `4181`。

## 思路

直接按定义递推：用两个变量 a、b 保存最近两项，从第 3 项起循环做 `t = a + b; a = b; b = t`，共推 k-2 次即可。k = 1、2 时直接输出 1；最大项 F(46) = 1836311903 在 int 范围内，但按习惯用 ll 存数据更稳。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
