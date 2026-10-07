---
oj: "roj"
problem_id: "2017"
title: "usaco-1.5.1 数字金字塔"
description: "逐层滚动一维 dp：走到当前层第 j 个数的最大和只由上一层正上方与左上方两格决定，末行最大值即答案。"
difficulty: "入门"
date: 2026-10-01 03:07
updated: 2026-10-06 09:32
toc: true
tags: ["动态规划", "usaco", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2017
---

[[TOC]]

## 题目描述

给定 $R$ 层数字金字塔（$1 \le R \le 1000$，每个数是不大于 100 的非负整数），第 $i$ 层有 $i$ 个数。从顶部出发，每步只能走到下一层的正下方或右下方，直到最底层，求路径上数字和的最大值。

样例输入首行为 `5`，金字塔为 `7 / 3 8 / 8 1 0 / 2 7 4 4 / 4 5 2 6 5`（`/` 表示换行）；输出 `30`（路径 $7 \to 3 \to 8 \to 7 \to 5$）。输出为单独一行，即最大路径和。

## 思路

设 $dp_j$ 表示走到当前层第 $j$ 个数的最大路径和。每个格子只能从上一层正上方或左上方两格到达，故 $dp_j = a_j + \max(dp_{j-1}, dp_j)$，越界的一项不存在直接忽略。自上而下逐层滚动更新，最后取末行的最大值即为答案。时间复杂度 $O(R^2)$，空间复杂度 $O(R)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
