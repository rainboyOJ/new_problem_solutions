---
oj: "roj"
problem_id: "1535"
title: "「一本通 4.1 例 1」数列操作"
description: "单点加与区间求和交替：树状数组按 lowbit 把前缀和拆成 O(log n) 段，修改沿链更新、查询两次前缀和相减，O(n + m log n)。"
difficulty: "普及-"
date: 2026-09-30 16:42
updated: 2026-10-06 00:35
toc: true
tags: ["树状数组", "前缀和", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1535
---

[[TOC]]

## 题目描述

给定长度为 $n$ 的序列与 $m$ 个操作，每个操作给出 $k,a,b$：$k=1$ 时把第 $a$ 个数加 $b$；否则求子数列 $[a,b]$ 的连续和并输出。数据范围 $n,m\leqslant10^6$。

## 思路

树状数组维护前缀和：单点修改沿 $i+\mathrm{lowbit}(i)$ 向上更新，区间查询沿 $i-\mathrm{lowbit}(i)$ 向下拆段，两次前缀和相减得区间和。注意真实数据中查询操作码为 $2$，代码判据写成 $k=1$ 为加法、其余为查询即可兼容样例与真实数据。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
