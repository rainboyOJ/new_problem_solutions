---
oj: "roj"
problem_id: "3504"
title: "[NOIP2001-普及]数的计数"
description: "把『n 左边加一个不超过 n/2 的数』的生成过程建成递推 f(n)=1+Σf(1..n/2)，相邻前缀和降为一维线性递推，预处理后 O(1) 回答。"
difficulty: "入门"
date: 2026-10-02 03:53
updated: 2026-10-06 12:16
toc: true
tags: ["入门", "动态规划", "递推", "前缀和", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3504
---

[[TOC]]

## 题目描述

给定自然数 $n$（$1 \leqslant n \leqslant 1000$），按如下规则处理：不作任何处理；或在 $n$ 左边加上一个不超过 $n$ 一半的自然数，加上的数继续按同样规则处理，直到不能再产生新数。求整个过程中（包含 $n$ 本身）能得到的不同数的个数。例如 $n=6$ 时能得到 $6, 16, 26, 36, 126, 136$ 共 $6$ 个。

**输入**：一个自然数 $n$。**输出**：满足条件的数的个数。**样例**：输入 `6`，输出 `6`。

## 思路

设 $f(n)$ 为从 $n$ 出发（含 $n$）能得到的数的个数：在 $n$ 左边拼上 $m\ (1 \leqslant m \leqslant \lfloor n/2 \rfloor)$ 后的产物与从 $m$ 出发的产物一一对应（拼接结果位数可反解，单射），故 $f(n) = 1 + \sum_{m=1}^{\lfloor n/2 \rfloor} f(m)$。求和部分恰是 $f$ 的连续前缀和，随递推维护 $s_n = s_{n-1} + f(n)$ 即可 $O(n)$ 递推后查表回答。注意最大答案 $1981471878$ 超过 `int` 范围，需用 `long long`。

## 参考代码

@include-code(./main.cpp, cpp)
