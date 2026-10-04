---
oj: "roj"
problem_id: "1223"
title: "An Easy Problem"
description: "求最小的比 n 大、且二进制中 1 的个数与 n 相同的数：对最低位 1 做一次 Gosper 进位，再把被清空的 1 补回最低位，单次 O(1)。"
difficulty: "普及-"
date: 2026-09-30 00:29
updated: 2026-10-05 05:57
toc: true
tags: ["位运算", "贪心", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1223
---

[[TOC]]
## 题目描述

给定一个正整数 $N$，求最小的、比 $N$ 大的正整数 $M$，使得 $M$ 与 $N$ 的二进制表示中有相同数目的 `1`。

例如 $N = 78 = (1001110)_2$ 有 4 个 `1`，满足条件的最小数是 $83 = (1010011)_2$。

输入若干行，每行一个数 $n$（$1 \le n \le 10^6$），输入 `0` 结束。对每个 $n$ 输出一行对应的值。

样例：输入 `1 / 2 / 3 / 4 / 78 / 0`，对应输出 `2 / 4 / 5 / 8 / 83`。

## 思路

把 $n$ 最低位那段连续的 `1` 整体进位一格（`low = n & -n`，`carried = n + low`），就完成了"变大"且 popcount 少了若干个 `1`；再把被清空的 `1` 补回最低位即可最小。被改动位为 `n ^ carried`，右移两位丢掉新产生的 `1`，再除以 `low` 折算到最低位，得到要补回的 `1` 串，按位或回去即为答案，单次询问 $O(1)$。

## 参考代码

@include-code(./main.cpp, cpp)
