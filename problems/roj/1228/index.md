---
oj: "roj"
problem_id: "1228"
title: "书架"
description: "贪心：把奶牛按高度从大到小排序，优先选最高的奶牛叠放，累计高度首次达到书架高度 B 时用掉的奶牛数即为答案。"
difficulty: "入门"
date: 2026-09-30 00:42
updated: 2026-10-05 05:58
toc: true
tags:
  - 贪心
  - 排序
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1228
---

[[TOC]]

## 题目描述

有 $N$ 头奶牛，第 $i$ 头高 $H_i$，要把若干头奶牛叠起来使总高度不低于书架高度 $B$，求最少用几头（$1\le N\le 20\,000$，$1\le H_i\le 10\,000$，$1\le B\le S<2\,000\,000\,007$，$S$ 为所有高度之和）。

输入第一行两个整数 $N,B$，接下来 $N$ 行每行一个 $H_i$；输出最少奶牛数。样例输入首行 `6 40`、随后六行依次为 `6 18 11 13 19 11`，输出 `3`。

## 思路

要让奶牛头数最少，就该让每头奶牛贡献的高度尽量大，所以把高度从大到小排序后依次累加，累加和首次 $\ge B$ 时用掉的奶牛数就是答案（$O(N\log N)$，瓶颈在排序）。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
