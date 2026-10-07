---
oj: "roj"
problem_id: "1094"
title: "与7无关的数"
description: "枚举 1..n，跳过 7 的倍数和各位含 7 的数，累加平方和；含 7 判断用逐位取个位，O(n) 直解。"
difficulty: "入门"
date: 2026-09-29 18:28
updated: 2026-10-05 00:49
toc: true
tags: ["入门", "数学", "枚举", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1094
---

[[TOC]]

## 题目描述

若正整数能被 $7$ 整除，或十进制表示中某一位是 $7$，称它与 $7$ 相关。给定 $n$（$n<100$），求所有满足 $1 \le i \le n$ 且与 $7$ 无关的正整数 $i$ 的平方和。输入一行一个正整数 $n$，输出一行一个整数即平方和；样例输入 `21`，输出 `2336`。

## 思路

枚举 $1 \dots n$，只有"不是 $7$ 的倍数"且"十进制各位都不含 $7$"时才累加 $i^2$；含 $7$ 的判断用逐位取个位再除以 $10$。$n<100$，$O(n)$ 直解。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
