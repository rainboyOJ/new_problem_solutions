---
oj: "roj"
problem_id: "1265"
title: "【例9.9】最长公共子序列"
description: "二维 DP 求两串最长公共子序列，滚动数组压到 O(m)。"
difficulty: "普及"
date: 2026-01-14 22:00
updated: 2026-10-05 07:28
toc: true
tags: ["DP", "LCS", "滚动数组"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1265"
---

[[TOC]]

## 题目描述

给定两个由大写字母组成的长度均不超过 1000 的字符串 X、Y；子序列是删去若干字符得到的串，公共子序列是同时属于两串的子序列。输入两行（分别为 X 和 Y），输出其最长公共子序列长度，无公共子序列则输出 0。数据范围：长度 ≤ 1000。

样例输入：`ABCBDAB` / `BDCABA`；样例输出：`4`。

## 思路

`dp[i][j]` 为 X[1..i] 与 Y[1..j] 的 LCS 长度；末字符相等则 `dp[i][j] = dp[i-1][j-1] + 1`，否则取 `max(dp[i-1][j], dp[i][j-1])`；用滚动数组保留两行即可，`j` 从小到大遍历。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)