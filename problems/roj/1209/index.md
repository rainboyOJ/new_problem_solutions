---
oj: "roj"
problem_id: "1209"
title: "分数求和"
description: "逐次通分相加并立即用 gcd 约分，保持最简后按整数或分数格式输出。"
difficulty: "入门"
date: 2026-09-29 23:39
updated: 2026-10-05 05:37
toc: true
tags: ["模拟", "gcd", "分数"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1209"
---

[[TOC]]

## 题目描述

输入 $n$（$1 \leqslant n \leqslant 10$）个分数并对它们求和，用最简形式表示结果：分子分母的最大公约数为 $1$；若分母为 $1$ 则直接输出整数，如 $\frac{3}{6}$ 化简为 $\frac{1}{2}$，$\frac{3}{1}$ 化简为 $3$。分子和分母均不为 $0$、不为负数。输入第一行是整数 $n$，接下来 $n$ 行每行一个 `p/q` 形式的分数（不含空格，$p, q$ 均不超过 $10$）；输出一行，即最终结果的最简形式，分数用 `p/q` 表示。

样例：输入第一行 `2`，接下来两行 `1/2`、`1/3`，输出 `5/6`。

## 思路

用一个分数 $(a, b)$（初始 $0/1$）做累加器，每读入 $p/q$ 就按 $\frac{a}{b}+\frac{p}{q}=\frac{aq+bp}{bq}$ 通分相加，并立即用 $\gcd$ 约分保持最简。全部加完后若分母为 $1$ 只输出整数，否则输出 $a/b$。

## 参考代码

@include-code(./main.cpp, cpp)
