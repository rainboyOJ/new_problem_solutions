---
oj: "roj"
problem_id: "1433"
title: "「一本通 1.2 例 1」愤怒的牛"
description: "把「最大的最小间距」转成单调可行性判定，用 O(N) 贪心判定给定间距能否放下 C 头牛，再在答案值域上二分。"
difficulty: "普及-"
date: 2026-09-30 10:09
updated: 2026-10-05 23:30
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1433
---

[[TOC]]

## 题目描述

农夫 John 的畜栏有 $N$ 个编号为 $x_i$ 的隔间（$2 \le N \le 10^5$，$0 \le x_i \le 10^9$），要把 $C$ 头牛（$2 \le C \le N$）分到互不相同的隔间里，使任意两头牛之间距离的最小值尽量大。求这个最大的最小距离。

输入：第一行 $N,C$，接下来 $N$ 行每行一个 $x_i$；输出：一个整数，即最大的最小距离。样例：输入 `5 3` / `1 2 8 4 9`，输出 `3`。

## 思路

最小值最大，转为二分答案：判定「间距至少 $d$ 能否放下 $C$ 头牛」。把位置排序后贪心，第一头牛放最左，之后每头都放第一个距离上一头至少 $d$ 的隔间，能放下 $C$ 头即可行。$d$ 越小越容易放下，可行性关于 $d$ 单调，于是在 $[1,(s_N-s_1)/(C-1)]$ 上二分最大的可行 $d$。

## 参考代码

@include-code(./main.cpp, cpp)
