---
oj: "roj"
problem_id: "1235"
title: "输出前k大的数"
description: "把数组降序排序后取前 k 项逐行输出；用 sort + greater<ll>() 翻成降序后取前 k 个。"
difficulty: "入门"
date: 2026-09-30 01:07
updated: 2026-10-05 06:12
toc: true
tags: ["排序", "数组", "入门"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1235
---

[[TOC]]
## 题目描述
给定长度为 $n$（$n<10^5$）的整数数组和 $k<n$，把前 $k$ 大的数从大到小逐行输出，元素可正可负、可重复；输入：第一行 $n$，第二行 $n$ 个整数（绝对值 $\le 10^8$），第三行 $k$。
样例：
```
10 4 5 6 9 8 7 1 2 3 0 5
→ 9 8 7 6 5
```
## 思路
用 `std::sort` 配 `greater<ll>()` 把数组排成降序，再取前 $k$ 项逐行输出即可。
## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)