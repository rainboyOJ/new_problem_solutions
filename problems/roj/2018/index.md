---
oj: "roj"
problem_id: "2018"
title: "usaco-1.5.2 回文质数"
description: "利用偶数位回文数必为11的倍数的性质，只构造奇数位回文数与11并在区间内试除判定素数。"
difficulty: "普及-"
date: 2026-10-01 03:06
updated: 2026-10-06 09:45
toc: true
tags:
  - 数论
  - 素数
  - 回文数
  - 构造
favorite: false
favorite_reason: ""
categories:
  - USACO
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2018
---
[[TOC]]

## 题目描述

因为 151 既是一个质数又是一个回文数（从左到右和从右到左读一样），所以 151 是回文质数。写一个程序找出范围 $[a, b]$（$5 \le a < b \le 100{,}000{,}000$）间的所有回文质数。

输入第 1 行是两个整数 $a$ 和 $b$。输出区间内所有回文质数，按升序一行一个。

样例输入 `5 500`，样例输出为 `5 7 11 101 131 151 181 191 313 353 373 383`，每行一个数。

## 思路

区间很大但回文数极少，所以不逐个数判断，而是按"前半段 + 中间位 + 反转前半段"直接构造 3、5、7 位回文数再试除判素。关键性质：偶数位回文数的奇偶位交错和为 0，必是 11 的倍数，因此除 11 外所有偶数位回文数都不是质数，只需再特判一位数和 11。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
