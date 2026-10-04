---
oj: "roj"
problem_id: "1126"
title: "矩阵转置"
description: "把 n×m 矩阵按定义转置：输出第 j 行 = 原矩阵第 j 列。外层枚举 j（1..m）、内层枚举 i（1..n），逐个输出 a[i][j]，O(nm)。"
difficulty: "入门"
date: 2026-09-29 20:02
updated: 2026-10-04 22:12
toc: true
tags: ["入门", "数组", "矩阵", "cpp"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1126
---
[[TOC]]

## 题目描述

输入一个 $n$ 行 $m$ 列的整数矩阵 $A$，输出它的转置 $A^T$：一个 $m$ 行 $n$ 列的矩阵，满足 $A^T[j][i]=A[i][j]$，即输出的第 $j$ 行恰好是原矩阵的第 $j$ 列。第一行包含 $n,m$（$1\le n,m\le 100$），随后 $n$ 行每行 $m$ 个 $1\sim 1000$ 的整数；输出 $m$ 行每行 $n$ 个整数，相邻数用一个空格隔开。样例：输入 `3 3 / 1 2 3 / 4 5 6 / 7 8 9`，输出 `1 4 7 / 2 5 8 / 3 6 9`。

## 思路

转置是纯下标重排，不含任何计算。外层枚举输出行 $j$（共 $m$ 个）、内层枚举 $i$（共 $n$ 个），按顺序输出 $a[i][j]$ 即可，复杂度 $O(nm)$，与读入同阶。

## 参考代码

@include-code(./main.cpp, cpp)
