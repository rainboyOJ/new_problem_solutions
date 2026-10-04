---
oj: "roj"
problem_id: "1154"
title: "亲和数"
description: "枚举 a 用真因数和 σ(n) 判定亲和数，σ(σ(a))=a 且 σ(a)≠a 即命中。"
difficulty: "普及-"
date: 2026-09-29 21:15
updated: 2026-10-05 03:44
toc: true
tags: ["普及-", "数论", "枚举", "因子", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1154
---

[[TOC]]

## 题目描述

自然数 $n$ 的真因子是指所有能整除 $n$ 且不等于 $n$ 的自然数。例如 $12$ 的真因子为 $1,2,3,4,6$，它们的和是 $16$。

若 $a$ 的真因子之和为 $b$，且 $b$ 的真因子之和又等于 $a$，并且 $a<b$，则称 $a,b$ 为一对"亲和数"。求最小的一对亲和数。

无输入。输出一行：$a$ 和 $b$，中间一个空格。

## 思路

写 `sigma(n)` 求 $n$ 的真因子和（因子成对出现，枚举 $d\le\sqrt n$，命中时把 $d$ 和 $n/d$ 两端一起收，完全平方数只收一次）；再从 $a=2$ 起递增枚举，第一次出现 $\sigma(\sigma(a))=a$ 且 $\sigma(a)\neq a$ 的 $a$ 即答案中较小者（完全数需排除）。

## 参考代码

@include-code(./main.cpp, cpp)