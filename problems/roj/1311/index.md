---
oj: "roj"
problem_id: "1311"
title: "【例2.5】求逆序对"
description: "把两两比较改写成逐个右端点统计「左边比它大的个数」，用树状数组做前缀和查询与单点加，O(n log n) 求出逆序对总数。"
difficulty: "普及-"
date: 2026-09-30 04:29
updated: 2026-10-05 08:58
toc: true
tags: ["树状数组", "离散化", "逆序对", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1311
---

[[TOC]]

## 题目描述

给定长度为 $n$ 的序列 $a_1, a_2, \dots, a_n$（$n \leqslant 10^5$，$a_i \leqslant 10^5$），求满足 $i < j$ 且 $a_i > a_j$ 的下标对 $(i, j)$ 的个数，即逆序对总数；相等不构成逆序对。第一行为 $n$，接下来 $n$ 行每行一个 $a_i$。样例 $a = [3, 2, 3, 2]$ 的答案为 $3$。

## 思路

从左往右扫，把已经扫过的元素装进树状数组（按值域维护的权值桶）；扫到 $x$ 时，先查前缀和得到「左边值 $\leqslant x$ 的个数」，再用「已插入元素总数」减去它，就是「左边比 $x$ 大」的个数，累加后把 $x$ 插入桶里。顺序必须是先查后插，否则 $x$ 会和自己配对。整体 $O(n \log V)$，$a_i \leqslant 10^5$ 直接开桶即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)