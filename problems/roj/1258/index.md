---
oj: "roj"
problem_id: "1258"
title: "【例9.2】数字金字塔"
description: "数塔 DP：自底向上递推 f(i,j)=a[i][j]+max(f(i+1,j),f(i+1,j+1))，滚动一维数组即可。"
difficulty: "普及-"
date: 2026-09-30 02:15
updated: 2026-10-06 02:35
toc: true
tags: ["动态规划", "线性DP", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "leetcodecn"
    problem_id: "pascals-triangle"
    reason: "数字金字塔把杨辉三角「由相邻两数相加得下一格」的二维递推骨架换成相邻两数取 max 再累加自身，逐层递推思路直接迁移，只是多了求最大值的取优步骤"
common: []
recommend: []
source: https://roj.ac.cn/problem/1258
---

[[TOC]]

## 题目描述

有一个 $R$ 层的数字金字塔，第 $i$ 层有 $i$ 个非负整数。一条路径从最高点出发，每步只能走到左下方或右下方的点，最终停在第 $R$ 层任意位置，路径的值为经过的所有数字之和，求这个和的最大值。
输入：第一行为 $R$（$1 \leqslant R \leqslant 1000$），随后 $R$ 行依次给出金字塔每一层的整数，所有数不超过 $100$；输出：单独一行，输出可能得到的最大和。
样例输入（$5$ 层，逐行给出）：`5 13 11 8 12 7 26 6 14 15 8 12 7 13 24 11`。
样例输出：`86`，对应最优路径 $13 \to 8 \to 26 \to 15 \to 24$。

## 思路

记 $f(i,j)$ 为从 $(i,j)$ 出发走到底部的最大数字和，则 $f(i,j) = a_{i,j} + \max(f(i+1,j),\, f(i+1,j+1))$，且 $f(R,j) = a_{R,j}$。
自底向上逐层递推，答案即 $f(1,1)$；每层只依赖下一层，用一维数组滚动即可，时间 $O(R^2)$、空间 $O(R)$。

## 参考代码

@include-code(./main.cpp, cpp)
