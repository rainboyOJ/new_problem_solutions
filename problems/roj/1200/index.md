---
oj: "roj"
problem_id: "1200"
title: "分解因数"
description: "设 f(n,lo) 为把 n 拆成不小于 lo 的因子之积的方案数，按首因子 d 分类递推 f(n,lo)=1+Σf(n/d,d)（d≤√n 且 d|n），记忆化即可"
difficulty: "普及-"
date: 2026-09-29 23:16
updated: 2026-10-06 02:35
toc: true
tags: ["搜索", "深度优先搜索", "记忆化搜索", "数学", "因数分解"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1318"
    reason: "A 用 start 下界保证非递减使每个无序拆分只数一次，B 把同一「下界收紧」去重步骤迁移到因数分解 f(n,lo) 并叠加记忆化与因子枚举"
common: []
recommend: []
source: https://roj.ac.cn/problem/1200
---

[[TOC]]

## 题目描述

给出正整数 $a>1$，把它分解成若干个正整数的乘积 $a=a_1\times a_2\times\cdots\times a_n$，要求 $1<a_1\leqslant a_2\leqslant\cdots\leqslant a_n$，问有多少种分解，$a=a$ 也算一种。输入第一行是数据组数 $n$，随后 $n$ 行每行一个 $a$（$1<a<32768$）；对每组数据输出一行分解种数。样例输入 `2` / `2` / `20` 对应输出 `1` / `4`。

## 思路

设 $f(n,lo)$ 为把 $n$ 拆成若干不小于 $lo$ 的因子之积的方案数，因子非降序写成 $lo\le d\le n/d$，即首因子只需枚举到 $\lfloor\sqrt n\rfloor$ 且 $d\mid n$，于是 $f(n,lo)=1+\sum_{d}f(n/d,d)$。初值 $1$ 对应"不再往下拆"即 $n$ 本身这一种分解，把下界从 $lo$ 收紧成 $d$ 保证每个无序分解只被数一次，答案是 $f(a,2)$。同一状态被不同分支反复用到，记忆化后即可。

## 参考代码

@include-code(./main.cpp, cpp)
