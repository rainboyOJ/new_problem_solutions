---
oj: "roj"
problem_id: "1318"
title: "自然数的拆分"
description: "用 DFS 按非递减顺序拆分 n，自然去重并按字典序输出所有方案。"
difficulty: "入门"
date: 2026-09-30 04:53
updated: 2026-10-05 09:19
toc: true
tags: ["DFS", "搜索", "整数拆分"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1318
---

[[TOC]]

## 题目描述

输入一个大于 1 的自然数 $n$，把 $n$ 拆分成若干小于 $n$ 的正整数之和，按字典序输出所有不同的拆分方案。顺序不同视为同一种方案。

## 思路

DFS 枚举时限制下一个加数不小于上一个加数，这样每种无序拆分只出现一次，且从小到大枚举天然满足字典序。剩余值为 0 时输出当前方案。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
