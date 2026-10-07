---
oj: "roj"
problem_id: "3545"
title: "[NOIP2006-普及] 开心的金明"
description: "把问题看成 0/1 背包，逐件物品倒序滚动一维数组求价格与重要度乘积和的最大值。"
difficulty: "普及-"
date: 2026-10-02 06:42
updated: 2026-10-06 13:35
toc: true
tags: ["动态规划", "01背包", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3545
---

[[TOC]]

## 题目描述

金明有 $N$ 元钱要买 $m$ 件物品，第 $j$ 件价格 $v_j$、重要度 $w_j$，每件至多买一次，求总价不超过 $N$ 时 $\sum v_j w_j$ 的最大值。（$N<30000$，$m<25$，$v\le 10000$，$1\le w\le 5$。）输入第一行 $N\ m$，随后 $m$ 行每行 $v\ p$；输出该最大值。样例：输入 `1000 5 / 800 2 / 400 5 / 300 5 / 400 3 / 200 2`，输出 `3900`。

## 思路

把每件物品看成重量 $v_j$、价值 $v_j w_j$ 的 0/1 背包，容量为 $N$。设 $f[c]$ 为花费不超过 $c$ 的最大乘积和，逐件物品倒序枚举 $c=N,\dots,v_j$，用 $f[c]=\max(f[c],\,f[c-v_j]+v_jw_j)$ 滚动更新。倒序保证下标 $c-v_j$ 尚未被本件物品更新，从而每件只选一次；时间 $O(mN)$、空间 $O(N)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
