---
oj: "roj"
problem_id: "10006"
title: "涨薪"
description: "让工资最小的 k=n-x-y 人前两年连续拿 C 被开除，幸存 x+y 人年年涨薪：前 x 大乘 3^m、接下来 y 大乘 2^m，取模输出。"
difficulty: "普及"
date: 2026-10-02 17:43
updated: 2026-10-04 21:36
toc: true
tags: ["贪心", "排序", "快速幂", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/10006
---

[[TOC]]

## 题目描述

公司有 $n$ 人，第 $i$ 人初始工资 $a_i$。每年选 $x$ 人绩效 A（工资 $\times 3$）、$y$ 人绩效 B（$\times 2$），其余绩效 C（工资不变），**连续两年绩效 C 会被开除**，且不招新人。输入第一行 $n,m,x,y$，第二行 $n$ 个 $a_i$；求 $m$ 年后在职员工工资总和的最大值，对 $10^9+7$ 取模。$1\leqslant n\leqslant 10^5$，$1\leqslant m\leqslant 10^9$，$1\leqslant a_i\leqslant 10^5$。

样例：`2 1 1 1` / `5 3` 输出 `21`；`2 2 0 0` / `5 2` 输出 `0`。

## 思路

工资降序排序后，$m\geqslant 2$ 时让最小的 $k=n-x-y$ 人前两年连续拿 C 被开除，此后在职者恰剩 $x+y$ 人年年涨薪、涨薪名额零浪费，故答案是 $3^m S_x+2^m(S_{x+y}-S_x)$，其中 $S_j$ 为前 $j$ 大工资之和。$m=1$ 时无人会被开除，拿 C 的人照领原工资，需再加 $S_n-S_{x+y}$。

## 参考代码

@include-code(./main.cpp, cpp)
