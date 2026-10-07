---
oj: "roj"
problem_id: "1157"
title: "哥德巴赫猜想"
description: "筛出 100 以内素数表，对每个偶数升序枚举第一个加数，首个两数皆素数的即为最小拆分。"
difficulty: "入门"
date: 2026-09-29 21:14
updated: 2026-10-05 03:53
toc: true
tags: ["入门", "枚举", "素数判定", "数学", "python"]
favorite: false
favorite_reason: ""
categories:
  - 数学
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1157
---

[[TOC]]

## 题目描述

对 $6$ 到 $100$ 的每个偶数 $n$，输出一行 `n=p+q`，其中 $p$、$q$ 均为素数，且 $p$ 取所有合法拆分中最小的那一个。

## 思路

先用埃氏筛一次性标好 $100$ 以内的素数表。然后对每个偶数 $n$，从 $3$ 开始按奇数升序枚举第一个加数 $p$，$q=n-p$，找到第一个 $p$、$q$ 都是素数的组合即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
