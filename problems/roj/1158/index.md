---
oj: "roj"
problem_id: "1158"
title: "求1+2+3+..."
description: "用递归求 1..N 的和：明确参数、出口 n=0、转移 n+sum_to(n-1) 三要素，调用链是一条直链，时间与栈空间均为 O(N)。"
difficulty: "入门"
date: 2026-09-29 21:25
updated: 2026-10-05 03:50
toc: true
tags: ["递推", "递归", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1158
---

[[TOC]]

## 题目描述

给定整数 $N$，用递归的方法求 $1+2+3+\cdots+N$ 的值。

输入一行整数 $N$，输出一行累加和。输入样例 `5` 输出样例 `15`。

数据范围：$1 \leqslant N \leqslant 13$。

## 思路

递归三要素：参数是当前上界 $n$，出口是 $n=0$ 返回 $0$，转移是 $n+\text{sum\_to}(n-1)$。递归深度为 $N$，时间与栈空间都是 $O(N)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
