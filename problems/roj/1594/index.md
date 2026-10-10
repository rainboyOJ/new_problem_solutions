---
oj: "roj"
problem_id: "1594"
title: "「一本通 5.4 练习 1」涂抹果酱"
description: "把每行压成不超过 48 个合法行状态，按逐列不同色的相容表逐行滚动递推，被固定的第 K 行把计数劈成上下独立两半再相乘。"
difficulty: "普及"
date: 2026-09-30 20:39
updated: 2026-10-06 00:55
toc: true
tags: ["动态规划", "计数", "网格", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1594
---

[[TOC]]

## 题目描述

$N \times M$ 网格每格染 $1/2/3$ 三色之一，要求上下左右相邻格子颜色不同。第 $K$ 行已固定，求合法染色方案数 $\bmod 10^6$，无解输出 $0$。$1 \le N \le 10000,\ 1 \le M \le 5$。

样例：$N=2,\ M=2,\ K=1$，固定行为 $2\ 3$，输出 $3$。

## 思路

$M \le 5$ 时一行合法染色最多 $48$ 种，先枚举行状态并预计算相容表（上下两行逐列不同色）。把固定行第 $K$ 行拆成上下两段独立递推：上半段从全 $1$ 向量滚到第 $K-1$ 行再贴固定行；下半段从固定行单位向量滚到第 $N$ 行后求和。两段结果相乘取模即为答案。若固定行自身相邻同色则直接输出 $0$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
