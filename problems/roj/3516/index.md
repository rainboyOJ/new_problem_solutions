---
oj: "roj"
problem_id: "3516"
title: "[NOIP2002-提高] 均分纸牌"
description: "链上每条边的净搬运量等于前缀盈余，盈余非零的边各搬一次即最优：答案就是非零前缀和的个数，一遍贪心 O(N)。"
difficulty: "普及-"
date: 2026-10-02 04:52
updated: 2026-10-06 12:43
toc: true
tags: ["贪心", "前缀和", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3516
---

[[TOC]]

## 题目描述

$N$ 堆纸牌（总数为 $N$ 的倍数），每次从一堆取任意张移到相邻堆，求使每堆等于平均值的最少移动次数（$N \le 100$）。

## 思路

前 $i$ 堆的盈余 $S_i$ 必须经边 $(i,i+1)$ 净搬运，故贪心从左到右每次把差额推给右邻，答案即非零前缀盈余的个数。

## 参考代码

@include-code(./main.cpp, cpp)
