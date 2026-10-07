---
oj: "roj"
problem_id: "1681"
title: "【模板】离散化"
description: "排序去重建立值表，对每个数二分求名次完成离散化，O(n log n)。"
difficulty: "普及-"
date: 2026-10-01 02:03
updated: 2026-10-06 02:00
toc: true
tags: [离散化, 二分查找, 排序]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1681
---

[[TOC]]

## 题目描述

给定 $n$ 个整数（可能有重复，$n \le 10^5$，数值可负）。把所有不同值由小到大编号，每个数替换成它的编号（重复值共用同一编号，编号从 1 开始），按原顺序输出。

输入：第一行整数 $N$，第二行 $N$ 个整数。输出：一行 $N$ 个编号。
样例：输入 `6 / 1 2 3 4 3 1000`，输出 `1 2 3 4 3 5`。

## 思路

排序后相邻去重得到递增值表，每个数的编号就是它在值表中第一次出现的位置，用 `lower_bound` 二分查询即可，总复杂度 $O(n \log n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
