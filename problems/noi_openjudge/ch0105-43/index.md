---
oj: "noi_openjudge"
problem_id: "ch0105-43"
title: "质因数分解"
description: "从小到大寻找第一个因子，利用两个不同质因子的乘积性质得到较大质数。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "枚举", "质数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/43/
---

[[TOC]]

### 题意

已知正整数 $n$ 是两个不同质数的乘积，输出其中较大的质数。

### 思路

从 $2$ 开始寻找能整除 $n$ 的最小因子。因为 $n$ 恰好是两个不同质数的乘积，这个最小因子就是较小质数，另一个因子 `number // divisor` 就是答案。

只需检查到 `divisor * divisor <= number`；若两个因子都大于平方根，它们的乘积会超过 $n$。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

最坏情况下枚举到 $\sqrt n$，时间复杂度为 $O(\sqrt n)$，额外空间复杂度为 $O(1)$。

### 总结

已知乘积结构时，找到一边的因子就能用整除立即得到另一边。
