---
oj: "roj"
problem_id: "10009"
title: "牛半仙的妹子gcd"
description: "由 gcd 结合律按前两数的 gcd 分桶，答案化为 cnt[g] 与单变量 gcd 和 sum[g] 的乘积和，O(n³) 降到 O(n²)。"
difficulty: "普及-"
date: 2026-10-02 17:39
updated: "2026-10-04 21:49"
toc: true
tags: ["数论", "gcd", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/10009
---

[[TOC]]

## 题目描述

牛半仙有 $n$ 个妹子，第 $i$ 个妹子的属性值为 $a_i = n - i + 1$（属性值序列为 $(n, n-1, \ldots, 1)$）。定义 $k$ 个妹子 $\{b_1, \ldots, b_k\}$ 的相同度为 $\gcd(a_{b_1}, \ldots, a_{b_k})$，求 $\sum_{i=1}^{n} \sum_{j=1}^{n} \sum_{k=1}^{n} \gcd(i, j, k)$（下标可重复，即全部 $n^3$ 个有序三元组）的值。

输入：一行一个正整数 $n$（40% 的数据 $n \leqslant 200$，100% 的数据 $n \leqslant 1000$）。输出：一行一个整数表示相同度之和。样例输入 `2`，样例输出 `9`：8 个有序三元组中只有 $(2,2,2)$ 的 gcd 为 2，其余 7 个都含 1、gcd 为 1，故 $7 \times 1 + 2 = 9$。

## 思路

属性值序列是 $1..n$ 的一个排列，故答案就是 $\sum_{i,j,k=1}^{n} \gcd(i,j,k)$。由 gcd 结合律 $\gcd(i,j,k) = \gcd(\gcd(i,j), k)$，按 $g = \gcd(i,j)$ 把全部数对分进互不相交的桶：$cnt[g]$ 为前两数 gcd 恰为 $g$ 的数对个数，$S(g) = \sum_{k=1}^{n} \gcd(g,k)$，答案为 $\sum_g cnt[g] \cdot S(g)$；$cnt$ 和 $S$ 各用一次 $O(n^2)$ 枚举求得，$n \leqslant 1000$ 轻松通过，注意答案超过 $2^{30}$ 要用 64 位整数。

## 参考代码

@include-code(./main.cpp, cpp)
