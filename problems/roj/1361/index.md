---
oj: "roj"
problem_id: "1361"
title: "产生数"
description: "把变换规则建成数字 0~9 的有向图，每位独立求传递闭包大小，由乘法原理把各位闭包大小相乘即答案，避免枚举所有整数。"
difficulty: "普及-"
date: 2026-09-30 07:02
updated: 2026-10-05 12:00
toc: true
tags: ["图论", "传递闭包", "乘法原理", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1361
---

[[TOC]]

## 题目描述

给定十进制整数 $n$（$n \leqslant 2000$）和 $k$ 条规则（$k \leqslant 15$），每条规则形如 $x \to y$（$y \neq 0$）。一次变换：从 $n$ 的十进制表示中选一个数位，若该位数字等于某条规则的 $x$，可把它替换成对应的 $y$。求对 $n$ 施加 $0$ 次或多次变换，能得到的**不同整数**的个数（含 $n$ 本身）。

## 思路

把数字 $0 \sim 9$ 看成 $10$ 个节点，每条规则 $x \to y$ 是一条有向边。对每位数字求传递闭包 $R(d)$（即该位能变成的所有数字集合），答案就是各位 $|R(s_i)|$ 的乘积。$y \neq 0$ 保证不会出现前导零歧义。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
