---
oj: "roj"
problem_id: "1195"
title: "判断整除"
description: "2^n 种符号方案只有 k 种余数状态：用布尔数组保存可达余数集合，逐个数字平移出 ±a_i 两支，O(nk) 判定余数 0 是否可达。"
difficulty: "普及-"
date: 2026-09-29 23:03
updated: 2026-10-05 05:11
toc: true
tags: ["动态规划", "位运算", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1195
---

[[TOC]]

## 题目描述

给定 $N$ 个正整数 $a_i$（$2 < N < 10000$，$2 < k < 100$，$0 \leqslant a_i \leqslant 10000$），在每个数前放 `+` 或 `-` 后求和；只要 $2^N$ 种符号方案中存在一种和为 $k$ 的倍数（$0$、$-3$、$-6$ 都算 $3$ 的倍数）就称该序列可被 $k$ 整除。输入第一行为 $N$ 与 $k$，第二行为 $N$ 个整数；输出 `YES` 或 `NO`。样例输入 `3 2` / `1 2 4`，样例输出 `NO`（$1$ 是唯一的奇数项，无论符号怎么取和都是奇数）。

## 思路

$2^N$ 种符号方案无法枚举，但前缀和只有 $k$ 种余数，余数相同的方案完全等价、可以合并。用 `reach[r]` 记录处理完前 $i$ 个数后哪些余数可达，初值只有 `reach[0] = 1`；每加入 $a_i$ 就由 $D_{i-1}$ 在模 $k$ 下平移出 $D_{i-1}+a_i$ 与 $D_{i-1}-a_i$ 两支，最后查 `reach[0]` 即可。因为只看余数，可以先把每个 $a_i$ 归约到 $a_i \bmod k$，总复杂度 $O(Nk)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
