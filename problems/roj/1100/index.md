---
oj: "roj"
problem_id: "1100"
title: "金币"
description: "第 k 块恰好 k 天、每天 k 枚，用平方和公式求完整块贡献，再补尾块。"
difficulty: "入门"
date: 2026-09-29 18:51
updated: 2026-10-05 01:08
toc: true
tags: ["数学", "递推", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1100
---

[[TOC]]

## 题目描述

国王按块发工资：第 1 块 1 天每天 1 枚，第 2 块 2 天每天 2 枚，第 3 块 3 天每天 3 枚，依此类推。给定天数 $days$（$1\leq days\leq 10000$），求累计金币数。

输入：一个整数 `days`。输出：累计金币数。

样例输入 `6`，输出 `14`。

## 思路

第 $k$ 块占 $k$ 天，前 $n$ 块共 $\frac{n(n+1)}{2}$ 天。先求不超过 `days` 的最大完整块编号 $n$，再算完整块的平方和与尾块 $r(n+1)$ 的贡献。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
