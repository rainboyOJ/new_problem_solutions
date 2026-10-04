---
oj: "roj"
problem_id: "1184"
title: "明明的随机数"
description: "把随机数本身当作桶的下标：写入即完成去重，按下标升序扫描即完成排序，时间 O(N+V)。"
difficulty: "入门"
date: 2026-09-29 22:38
updated: 2026-10-05 04:41
toc: true
tags: ["桶排序", "计数排序", "排序", "去重", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1184
---

[[TOC]]
## 题目描述

明明生成了 $N$（$N \leq 100$）个 $1$ 到 $1000$ 之间的随机整数，重复的数字只保留一个，再把这些数从小到大排序，请完成「去重」与「排序」。输入第 1 行为正整数 $N$，第 2 行为 $N$ 个用空格隔开的正整数；输出第 1 行为不相同的随机数个数 $M$，第 2 行为从小到大排好序的 $M$ 个正整数。
```text
输入: 10 / 20 40 32 67 40 20 89 300 400 15
输出: 8 / 15 20 32 40 67 89 300 400
```
## 思路

值域只有 $[1,1000]$，读到数字 $v$ 就执行 `bucket[v] = 1`，重复写同一格即完成去重；输出时按下标 $1$ 到 $1000$ 扫描，下标递增方向就是数值递增方向，天然有序。总时间 $O(N+V)$。

## 参考代码

@include-code(./main.cpp, cpp)
