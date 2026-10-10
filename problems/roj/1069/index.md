---
oj: "roj"
problem_id: "1069"
title: "乘方计算"
description: "读入整数 a 与正整数 n，按 n≤10^4 且 |a^n|≤10^6 的保证直接循环累乘输出 a^n。"
difficulty: "入门"
date: 2026-09-29 17:09
updated: 2026-10-05 00:04
toc: true
tags: ["入门", "数学", "cpp"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1069
---

[[TOC]]

## 题目描述

给定整数 $a$ 和正整数 $n$（$-10^6\le a\le 10^6$，$1\le n\le 10^4$），求 $a^n$。一行输入两个整数 $a$、$n$，输出一个整数（题目保证 $|a^n|\le 10^6$）。样例：$2\ 3$ → $8$。

## 思路

把 result 初始化为 1，循环 n 次乘上 a 即可；题面保证 $|a^n|\le 10^6$，中间结果随 $k$ 单调不超界，int 累乘不会溢出。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)