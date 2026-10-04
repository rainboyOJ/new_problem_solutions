---
oj: "roj"
problem_id: "1281"
title: "最长上升子序列"
description: "按长度归类维护最小结尾数组 tails，用二分查找把朴素 O(N²) DP 优化为每元素一次定位的 O(N log N) 贪心扫描。"
difficulty: "入门"
date: 2026-09-30 03:02
updated: 2026-10-05 07:50
toc: true
tags: ["lis", "贪心", "二分", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1281
---

[[TOC]]

## 题目描述

给定长度为 $N$（$1 \le N \le 1000$）的整数序列 $(a_1,a_2,\dots,a_N)$，取下标严格递增的子序列 $i_1 < i_2 < \dots < i_K$，要求元素严格递增 $a_{i_1} < a_{i_2} < \dots < a_{i_K}$，求最大的 $K$。每个元素取值范围 $0 \sim 10000$。

样例输入 `7 / 1 7 3 5 9 4 8`，其中 $1<3<5<8$ 是一条最长上升子序列，输出 $4$。

## 思路

维护 `tails[L]` 表示长度 $L$ 的上升子序列的最小结尾；扫描序列时，对每个值 `v` 在严格递增的 `tails` 上二分找第一个 `>= v` 的位置，能追加就追加，否则原地替换更小结尾；每个元素一次二分，$O(N \log N)$ 得到 LIS 长度。

## 参考代码

@include-code(./main.cpp, cpp)
