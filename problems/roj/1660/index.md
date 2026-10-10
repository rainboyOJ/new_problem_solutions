---
oj: "roj"
problem_id: "1660"
title: "「一本通 6.6 练习 9」网格"
description: "网格路径计数不越过对角线：反射法推出 C(n+m,m)-C(n+m,m-1)，C++ 大整数精确输出。"
difficulty: "普及"
date: 2026-10-01 00:33
updated: 2026-10-07 13:50
toc: true
tags: ["数学", "组合计数", "卡特兰数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1194"
    reason: "B 在 A 教的「把整条路线数写成组合数」这一步之上叠加反射法，再用组合数差得广义卡特兰数"
common: []
recommend: []
source: https://roj.ac.cn/problem/1660
---

[[TOC]]

## 题目描述

从 $(0,0)$ 走到 $(n,m)$，只能向右或向上，且途经点满足 $x \ge y$。求方案总数。$1 \le m \le n \le 5000$，精确输出。
**输入**：一行两个整数 $n,m$。  
**输出**：一个整数，表示方案数。  
**样例**：输入 `6 6`，输出 `132`。

## 思路

反射法：总路径 $\binom{n+m}{m}$ 减去首次越过 $y=x+1$ 的坏路径 $\binom{n+m}{m-1}$，答案为两者之差。用质因数分解实现大整数精确计算。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
