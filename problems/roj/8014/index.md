---
oj: "roj"
problem_id: "8014"
title: "迟到的生日"
description: "前缀和作差 sum floor(n/d)，整除分块 O(√n) 求区间约数个数和。"
difficulty: "普及"
date: 2026-10-02 16:47
updated: 2026-10-06 16:51
toc: true
tags: ["整除分块", "约数", "数论", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/8014
---

[[TOC]]

## 题目描述

给定区间 $[t_1, t_2]$（$1 \le t_1 \le t_2 \le 10^7$），求每个数的正约数个数之和。输入为两个整数 $t_1\ t_2$，输出该和。

样例输入 `2 6`，输出 `13`（$2+2+3+2+4=13$）。

## 思路

设 $S(n)=\sum_{k=1}^{n}d(k)$，答案为 $S(t_2)-S(t_1-1)$。交换求和顺序得 $S(n)=\sum_{d=1}^{n}\lfloor n/d\rfloor$。商 $\lfloor n/d\rfloor$ 只有 $O(\sqrt n)$ 种，相同商的 $d$ 构成连续区间 $[l,r]$，其中 $r=\lfloor n/\lfloor n/l\rfloor\rfloor$，整段贡献为 $\lfloor n/l\rfloor\cdot(r-l+1)$。

## 参考代码

@include-code(./main.cpp, cpp)
