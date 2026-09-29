---
oj: "roj"
problem_id: "1151"
title: "素数个数"
description: "用埃拉托斯特尼筛法在 O(n log log n) 时间内统计 [2, n] 中的素数个数。"
difficulty: "入门"
date: 2026-09-29 21:02
updated: 2026-09-29 21:03
toc: true
tags: ["数论", "素数", "筛法"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1151
---

[[TOC]]

## 形式化题目

给定整数 $n$（$2 \leqslant n \leqslant 50000$），求区间 $[2, n]$ 中素数的个数。

## 正解

### 思路

最朴素的想法是：对每个 $x \in [2, n]$ 单独判断是否为素数，单次判断 $O(\sqrt x)$，总复杂度 $O(n\sqrt n)$。在 $n = 50000$ 时虽然可以通过，但存在一个更优雅且效率更高的方法——埃拉托斯特尼筛法。

核心观察：若 $p$ 是素数，则 $p^2, p^2+p, p^2+2p, \dots$ 必然都是合数。我们从小到大枚举每个素数 $p$，把它的倍数全部标记为合数。这样，当所有不超过 $\sqrt n$ 的素数都处理完后，仍未被标记的数就是素数。

为什么从 $p^2$ 开始标记？因为小于 $p^2$ 的 $p$ 的倍数 $kp$（其中 $k < p$）一定含有比 $p$ 小的素因子，已经被之前的素数筛掉了。只需从 $p^2$ 开始即可保证不重不漏。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n \log \log n)$。
- 空间复杂度：$O(n)$。

## 总结

本题是素数筛的入门模板。通过布尔数组记录每个数是否被标记为合数，利用“素数的倍数必为合数”这一性质，可以在近线性时间内统计出区间 $[2, n]$ 中的素数个数。
