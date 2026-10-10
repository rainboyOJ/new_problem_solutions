---
oj: "roj"
problem_id: "20003"
title: "最大整数"
description: "把数字当字符串，按 a+b > b+a 降序排序后拼接，即得最大整数。"
difficulty: "普及-"
date: 2026-10-02 19:16
updated: 2026-10-06 02:11
toc: true
tags: ["贪心", "排序", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20003
---

[[TOC]]

## 题目描述

给定 $n$ 个正整数，把它们首尾相接拼成一个多位整数，求最大可能值。

输入：第一行 $n$，第二行 $n$ 个正整数。输出：拼接后的最大数。

样例：$13\ 312\ 343$ 拼成 $34331213$。

## 思路

对任意两数 $a,b$，若 $ab>ba$ 则 $a$ 应排在 $b$ 前。按此规则排序后顺次拼接即得最优解。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
