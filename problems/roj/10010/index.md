---
oj: "roj"
problem_id: "10010"
title: "石子"
description: "判定唯一必胜态：只剩一堆且为偶数时 Alice 一次拿光，其余情况 Bob 总能拖延致胜。"
difficulty: "普及-"
date: 2026-10-02 17:38
updated: 2026-10-04 22:06
toc: true
tags: ["博弈论", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/10010
---

[[TOC]]

## 题目描述

Alice 与 Bob 玩石子。多组数据（读到 EOF），每组给定 $n$ 堆石子，第 $i$ 堆 $a_i$ 颗。Alice 先手，每次必须拿偶数颗（至少 2 颗）；Bob 每次必须拿奇数颗（至少 1 颗）。无法操作者输。$\sum n < 10^6$，$1 \leqslant a_i < 10^9$。

## 思路

Alice 只能拿偶数颗，因此她一次拿光的唯一可能是某堆本身为偶数且这是最后一堆；其余情况下 Bob 总能在任意非空堆拿 1 颗续命，把必败局面留给 Alice。故仅当 $n = 1$ 且 $a_1$ 为偶数时输出 `YES`，否则输出 `NO`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
