---
oj: "roj"
problem_id: "1092"
title: "求出e的值"
description: "用前缀积递推 k!，累加 1/k! 并保留 10 位小数输出。"
difficulty: "入门"
date: 2026-09-29 18:16
updated: 2026-10-05 00:48
toc: true
tags: ["入门", "数学", "浮点数"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1092
---

[[TOC]]

## 题目描述

给定整数 $n$（$2 \leqslant n \leqslant 15$），按公式

$$e = 1 + \frac{1}{1!} + \frac{1}{2!} + \cdots + \frac{1}{n!}$$

计算部分和，保留小数点后 10 位输出。

## 思路

维护一个递推的阶乘 `fact`，从 $1!$ 乘到 $n!$，每步把 $1/fact$ 累加到答案。这样一次扫描即可得到结果，时间复杂度 $O(n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
