---
oj: "roj"
problem_id: "1289"
title: "拦截导弹"
description: "按结尾位置合并子问题：f[i] 记录以 h[i] 结尾的最长不增子序列长度，转移在前面不低于 h[i] 的位置里取最大，O(n²) 后对全体取最大。"
difficulty: "普及-"
date: 2026-09-30 03:27
updated: 2026-10-05 08:09
toc: true
tags: ["动态规划", "最长不上升子序列", "线性DP", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1289
---

[[TOC]]

## 题目描述

给定依次飞来的 $n$ 枚导弹高度，一套系统第一发可任意高，之后每一发都不能高于前一发。求最多能拦截多少枚导弹。$n \le 15$，高度为不超过 $30000$ 的正整数。

输入第一行为 $n$，第二行为 $n$ 个高度。输出一个整数表示最多拦截数。

样例：$8$ / $389\ 207\ 155\ 300\ 299\ 170\ 158\ 65$，输出 $6$。

## 思路

设 $f[i]$ 为以第 $i$ 枚导弹结尾的最长不增子序列长度。枚举前面满足 $h_j \ge h_i$ 的 $j$，$f[i]=\max(f[j]+1)$，空则取 $1$。答案为 $\max\limits_i f[i]$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
