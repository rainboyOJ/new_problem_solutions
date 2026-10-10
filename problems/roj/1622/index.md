---
oj: "roj"
problem_id: "1622"
title: "「一本通 6.2 练习 3」Goldbach's Conjecture"
description: "欧拉筛预处理素数表，每次询问贪心取最小的奇素数 a，并 O(1) 判断 n - a 是否为素数。"
difficulty: "普及-"
date: 2026-09-30 22:31
updated: 2026-10-06 01:19
toc: true
tags:
  - "数论"
  - "素数筛法"
  - "贪心"
favorite: false
favorite_reason: ""
categories:
  - "数学"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1622
---

[[TOC]]

## 题目描述

哥德巴赫猜想：任何大于 $4$ 的偶数都能拆成两个奇素数之和。多组询问，每组给出一个 $n$，以 $0$ 结束；对每个 $n$ 输出使 $b-a$ 最大的一组分解 $n = a + b$（$a,b$ 为奇素数），无解则输出 `Goldbach's conjecture is wrong.`。数据范围 $6 \le n \le 10^6$。样例输入为 `8`、`20`、`42` 各一行并以 `0` 结束，输出为 `8 = 3 + 5`、`20 = 3 + 17`、`42 = 5 + 37`。

## 思路

因为 $b - a = n - 2a$ 随 $a$ 增大而减小，所以取使 $n-a$ 为素数的最小奇素数 $a$ 即为答案。先用欧拉筛在 $10^6$ 内打出素数表与判定表，每次询问从最小的奇素数开始枚举，$O(1)$ 判断 $n-a$ 是否素数，找到即输出。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
