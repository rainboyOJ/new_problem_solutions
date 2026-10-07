---
oj: "roj"
problem_id: "3509"
title: "数的划分"
description: "把 n 拆成 k 份不计顺序的正整数：按最小值是否为 1 二分得到 p_k(n)=p_{k-1}(n-1)+p_k(n-k)，记忆化搜索 O(nk) 计数。"
difficulty: "普及-"
date: 2026-10-02 04:40
updated: 2026-10-06 12:31
toc: true
tags: ["动态规划", "记忆化搜索", "整数分拆", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3509
---

[[TOC]]

## 题目描述

将整数 $n$ 分成 $k$ 份，每份不能为空，方案不考虑顺序。$6 < n \le 200$，$2 \le k \le 6$。输入 $n,k$，输出不同分法的种数。样例 $7\ 3$ 输出 $4$。

## 思路

设 $p_k(n)$ 为把 $n$ 拆成 $k$ 个正整数且不计顺序的方案数。按最小值是否为 $1$ 分类：最小值是 $1$ 时去掉一个 $1$，得到 $p_{k-1}(n-1)$；最小值 $\ge 2$ 时每份减 $1$，得到 $p_k(n-k)$。于是 $p_k(n)=p_{k-1}(n-1)+p_k(n-k)$，边界 $n<k$ 为 $0$、$k=1$ 为 $1$。记忆化搜索即可，状态数 $O(nk)$。

## 参考代码

@include-code(./main.cpp, cpp)
