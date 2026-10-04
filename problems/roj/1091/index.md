---
oj: "roj"
problem_id: "1091"
title: "求阶乘的和"
description: "线性递推阶乘并同步累加，用 accumulate 一行生成阶乘序列后求和。"
difficulty: "入门"
date: 2026-09-29 18:16
updated: 2026-09-29 18:16
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

## 形式化题目

给定正整数 $n$（$1 < n < 12$），求

$$
S = \sum_{i=1}^{n} i! = 1! + 2! + \cdots + n!
$$

## 正解

### 思路

最朴素的办法是对每个 $i$ 单独算 $i!$，再全部相加。但阶乘满足递推关系

$$
i! = i \times (i-1)!
$$

因此可以从 $1!$ 开始，一边递推当前阶乘值，一边把结果累加到答案里，这样只需要一次 $O(n)$ 的扫描。

具体实现用 `itertools.accumulate` 维护阶乘序列：初始值设为 $0! = 1$，对 $i = 1 \dots n$ 做 $f_i = i \times f_{i-1}$，最后把所有阶乘加起来再减去初始的 $0!$ 即可。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n)$，仅一轮线性递推。
- 空间复杂度：$O(n)$，存放生成的阶乘序列。

## 总结

本题是直接的阶乘递推累加。关键观察是 $i!$ 可由 $(i-1)!$ 推出，避免重复乘法，从而把复杂度降到线性。
