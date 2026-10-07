---
oj: "roj"
problem_id: "1546"
title: "「一本通 4.2 练习 3」选择客栈"
description: "从左到右扫描，用 covered[c] 维护位置已进入最靠右便宜咖啡店左侧的同色客栈数，答案每次累加 covered[c_j]，O(n) 时间、O(k) 空间。"
difficulty: "普及"
date: 2026-09-30 17:20
updated: 2026-10-06 02:35
toc: true
tags: ["计数", "思维", "python"]
favorite: false
favorite_reason: ""
categories: ["一本通"]
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P9244"
    reason: "B 直接沿用 A 教过的「固定右端点、合法左端点构成随右端点单调推进的前缀并一趟增量计数」这一骨架，只是把 A 的单计数器前缀计数换成按色调的 total 减 pend 记账，并叠加最靠右便宜店阈值 g(j) 与清账流程。"
common: []
recommend: []
source: https://roj.ac.cn/problem/1546
---

[[TOC]]

## 题目描述

丽江河边有 $n$ 家客栈排成一行，第 $i$ 家色调为 $c_i\in[0,k-1]$、咖啡店最低消费为 $b_i$。两人要住在色调相同的两家不同客栈，且两客栈之间（含两端）至少有一家咖啡店的最低消费不超过 $p$，求方案数。

输入第一行 $n,k,p$，之后 $n$ 行每行两个整数 $c_i,b_i$；输出一行一个整数表示方案数。样例输入 `5 2 3` / `0 5` / `1 3` / `0 2` / `1 4` / `1 5`，样例输出 `3`；$2\le n\le 2\times10^6$，$0<k<10^4$，$0\le p\le100$，$0\le b_i\le100$。

## 思路

对固定右端点 $j$，左端点 $i$ 越靠左区间越长、最小消费只降不升，故合法左端点恰是位置不超过 $g(j)$ 的同色客栈，$g(j)$ 为 $j$ 之前（含 $j$）最靠右的便宜咖啡店（$b\le p$），且随 $j$ 单调不降。从左到右扫描，用 `covered[c]` 维护位置已进入 $g$ 左侧的同色客栈数，随 $g$ 推进把新位置逐个计入，答案每次累加 `covered[c_j]`。时间 $O(n)$、空间 $O(k)$。

## 参考代码

@include-code(./main.cpp, cpp)
