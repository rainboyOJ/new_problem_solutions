---
oj: "roj"
problem_id: "1091"
title: "求阶乘的和"
description: "从 1! 开始递推阶乘并同步累加，一遍循环求出 1!+2!+...+n!。"
difficulty: "入门"
date: 2026-09-29 18:16
updated: 2026-10-05 00:48
toc: true
tags: ["数学", "递推", "前缀和"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1091
---

[[TOC]]

## 题目描述

给定正整数 $n$（$1 < n < 12$），求不大于 $n$ 的正整数的阶乘的和，即 $S = 1! + 2! + \cdots + n!$，输出 $S$。

输入一行一个正整数 $n$；输出一行阶乘的和。例如输入 `5`，输出 `153`（$1!+2!+3!+4!+5! = 153$）。

## 思路

利用递推关系 $i! = i \times (i-1)!$，维护当前阶乘值 `f`，初始为 $1$（即 $1!$），从 $1$ 到 $n$ 每轮先乘 $i$ 再累加到答案。$n < 12$ 时 $n! \le 11! \approx 4 \times 10^7$，用 `long long` 存答案即可，总复杂度 $O(n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
