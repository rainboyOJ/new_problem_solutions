---
oj: "roj"
problem_id: "1009"
title: "带余除法"
description: "C++ 的 / 向零截断、% 符号随被除数，正是评测数据采用的带余除法语义，直接输出 a/b 与 a%b 即可。"
difficulty: "入门"
date: 2026-09-29 13:07
updated: 2026-10-04 22:22
toc: true
tags: ["输入输出", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1009
---

[[TOC]]

## 题目描述

给定被除数 $a$ 与非零除数 $b$，求整数商 $q$ 与余数 $r$，满足 $a = q \cdot b + r$ 且 $|r| < |b|$，用默认的整除和取余运算即可，无需特殊处理。输入一行两个整数 $a,b$（$b \ne 0$）；输出一行两个整数，依次为商与余数。样例输入 `10 3`，样例输出 `3 1`。

## 思路

C++ 的 `/` 向零截断、`%` 的符号随被除数，恰好就是评测数据采用的语义，所以商直接取 `a / b`、余数直接取 `a % b` 输出即可，不必做任何修正。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
