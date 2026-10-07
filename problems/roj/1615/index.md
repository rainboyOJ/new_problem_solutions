---
oj: "roj"
problem_id: "1615"
title: "「一本通 6.1 例 1」序列的第 k 个数"
description: "判型后套用通项：等差 O(1)，等比用快速幂 O(log k)。"
difficulty: "入门"
date: 2026-09-30 22:17
updated: 2026-10-06 01:04
toc: true
tags: ["入门", "数学", "一本通", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1615
---

[[TOC]]

## 题目描述

BSNY 已知一个数列的前三项 $a,b,c$，该数列要么为等差数列、要么为等比数列。给定 $k$，求第 $k$ 项对 $200907$ 取模的值。多组数据。

输入：先读 $T$，随后 $T$ 行每行 $a\ b\ c\ k$。输出：每组一行答案。

数据范围：$1\le T\le100,\ 1\le a\le b\le c\le10^9,\ 1\le k\le10^9$。

## 思路

若 $2b=a+c$ 则为等差数列，公差 $d=b-a$，答案为 $a+(k-1)d$。否则为等比数列，公比 $r=b/a$，答案为 $a\cdot r^{k-1}\bmod 200907$，其中幂用快速幂在模意义下计算。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
