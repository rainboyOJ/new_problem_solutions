---
oj: "roj"
problem_id: "1108"
title: "向量点积计算"
description: "读入 n 与两个 n 维向量，按同下标配对相乘后累加输出点积。"
difficulty: "入门"
date: 2026-09-29 19:14
updated: 2026-10-05 01:40
toc: true
tags: ["入门", "数学", "数组", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1108
---

[[TOC]]

## 题目描述

给两个 $n$ 维整数向量，求点积 $a\cdot b=\sum a_i b_i$。

输入第一行为 $n$（$1\le n\le1000$），第二、三行各 $n$ 个整数；输出一个整数。

样例：$3$，$1\ 4\ 6$，$2\ 1\ 5$ → $36$。

## 思路

同下标配对相乘再累加，单次扫描 $O(n)$；结果用 `long long` 累加即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
