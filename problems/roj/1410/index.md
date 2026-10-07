---
oj: "roj"
problem_id: "1410"
title: "最大质因子序列"
description: "对区间每个数从小到大试除，除尽当前因子后剩下的商就是最大质因子，单次 O(√n)。"
difficulty: "入门"
date: 2026-09-30 09:12
updated: 2026-10-05 23:10
toc: true
tags:
  - 数论
  - 质因数分解
favorite: false
favorite_reason: ""
categories:
  - 数论
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1410
---

[[TOC]]

## 题目描述

给定两个正整数 m, n（m ≤ n），对区间 [m, n] 中每个整数 i 求其最大质因子，并按 i 从小到大用逗号间隔输出。输入一行两个正整数 m, n，空格间隔；输出一行，即答案序列。

样例输入 `5 10`，样例输出 `5,3,7,2,3,5`（依次对应 5,6,7,8,9,10 的最大质因子）。

## 思路

对每个数从小到大试除因子并除尽：更小的因子已除尽，当前因子必为质数，省去单独判质数；循环结束时剩下的商就是最大质因子。因子只需试到 √N，2 之后只试奇数。

## 参考代码

@include-code(./main.cpp, cpp)
