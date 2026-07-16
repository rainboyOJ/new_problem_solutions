---
oj: "luogu"
problem_id: "CF912E"
title: "Prime Gift"
description: "把质数拆成两组生成所有乘积，二分答案并双指针统计不超过它的乘积对数。"
difficulty: "省选/NOI-"
date: 2026-07-16 20:10
toc: true
tags: ["Meet-in-the-Middle", "二分答案", "数论", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/CF912E
---

[[TOC]]

### 题意

给定至多 16 个质数，求所有质因子都来自该集合的第 `k` 小正整数，答案不超过 $10^{18}$。

### 思路

把质数交错分到两组，分别 DFS 枚举不超过 $10^{18}$ 的所有质数幂乘积。每个合法数唯一写成 `left * right`。

二分候选答案 `limit`。两边乘积列表升序后，用一个只向左移动的右指针统计满足 `left[i] * right[j] <= limit` 的配对数。计数至少 `k` 时收缩上界。

乘法比较写成 `left > limit // right`，避免其他语言中的 64 位溢出。

### Python 知识

- `primes[::2]` 与 `primes[1::2]` 交错拆分，比按连续位置切分更平衡小质数。
- 递归中的 `while` 自然枚举某质数指数为 0、1、2……。
- Python 大整数不会溢出，但除法比较仍更便于迁移到 C++。

### 代码

@include-code(./main.py, python)

### 复杂度

设两边乘积数为 $A,B$，生成与排序 $O(A\log A+B\log B)$，二分计数 $O((A+B)\log 10^{18})$。

### 总结

乘法闭包看似无限，但答案上界让每组可枚举；折半后再二分秩是核心组合。
