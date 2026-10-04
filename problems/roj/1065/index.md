---
oj: "roj"
problem_id: "1065"
title: "奇数求和"
description: "端点按奇偶收缩到首末奇数后套等差数列公式，O(1) 算闭区间奇数和；区间内无奇数时项数自然为 0，无需分支。"
difficulty: "入门"
date: 2026-09-29 16:58
updated: 2026-10-04 23:57
toc: true
tags:
  - 循环结构
  - 等差数列
  - 位运算
  - Python
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1065
---

[[TOC]]

## 题目描述

给定两个数 $m, n$（$0 \leqslant m \leqslant n \leqslant 300$），求闭区间 $[m, n]$ 内所有奇数之和。输入一行 $m$ $n$（一个空格分开），输出一行一个整数表示答案。样例输入 `7 15`，输出 `55`（即 $7+9+11+13+15$）。

## 思路

把端点按奇偶挪到区间内首末奇数，再套等差数列求和公式 $S=(a_1+a_k)k/2$；无奇数时项数公式自然得 0，免分支。

## 参考代码

@include-code(./main.cpp, cpp)