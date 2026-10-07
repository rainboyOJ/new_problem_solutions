---
oj: "roj"
problem_id: "1086"
title: "角谷猜想"
description: "按奇偶分支模拟角谷变换，每步输出算式，直到当前数变为 1。"
difficulty: "入门"
date: 2026-09-29 18:05
updated: 2026-10-05 00:33
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1086"
---

[[TOC]]

## 题目描述

对正整数 $N\,(N\leqslant 2\,000\,000)$ 反复变换：奇数则乘 $3$ 加 $1$，偶数则除以 $2$，直到得到 $1$。输出每步算式（每步一行），最后一行输出 `End`；若输入为 $1$ 则直接输出 `End`。样例：输入 `5`，输出 `5*3+1=16`、`16/2=8`、`8/2=4`、`4/2=2`、`2/2=1`、`End`。

## 思路

直接模拟：维护当前值 $n$，当 $n\neq 1$ 时按奇偶性算出下一步并输出等式，最后输出 `End`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
