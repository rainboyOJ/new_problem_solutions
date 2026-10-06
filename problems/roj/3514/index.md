---
oj: "roj"
problem_id: "3514"
title: "[NOIP2002-普及] 产生数"
description: "把数字变换规则建成 10 个点的有向图，用位集 Floyd 求传递闭包，答案为每位可达数字个数的乘积（unsigned __int128）。"
difficulty: "普及"
date: 2026-10-02 04:41
updated: 2026-10-06 12:40
toc: true
tags: ["图论", "传递闭包", "乘法原理", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3514
---

[[TOC]]

## 题目描述

给定整数 $n$（$n < 10^{30}$）和 $k$（$k \leqslant 15$）条一位数变换规则 $x \to y$（$y \neq 0$）。可对 $n$ 的任意一位做任意次（含 0 次）变换，求能产生的不同整数个数（含 $n$ 本身）。
输入：第一行 `n k`，接下来 $k$ 行每行一条规则 `x y`；输出：一个整数。样例：输入 `234 2`、规则 `2 5`、`3 6` 时输出 `4`（234、534、264、564）。

## 思路

把数字 $0 \sim 9$ 看成图上结点，规则 $x \to y$ 是有向边，"数字 $d$ 经任意次变换能变成的数字集合"就是从 $d$ 出发的可达点集（含自身），用位集 Floyd 求传递闭包。每位数字 $d$ 有 $\mathrm{popcount}(g[d])$ 种取值，各位独立，由乘法原理答案为所有位的可达个数之积。答案可达 $10^{30}$ 量级，超出 64 位整数，用 `unsigned __int128` 计算。

## 参考代码

@include-code(./main.cpp, cpp)
