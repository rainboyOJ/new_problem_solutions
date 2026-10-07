---
oj: "roj"
problem_id: "1616"
title: "「一本通 6.1 练习 1」A 的 B 次方"
description: "指数 b 可达 10^9，用二进制拆分把 a^b 化成若干 a^(2^k) 之积再相乘，Python 三参数 pow 一步完成 O(log b) 模幂。"
difficulty: "入门"
date: 2026-09-30 22:18
updated: 2026-10-06 01:04
toc: true
tags: ["数学", "快速幂", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1616
---

[[TOC]]

## 题目描述

给定正整数 $a,b,m$（$1\le a,b,m\le 10^9$），求 $a^b\bmod m$。

输入一行三个整数 $a,b,m$；输出一个整数表示结果。

样例输入：`2 100 1007`，样例输出：`169`。

## 思路

把指数 $b$ 拆成二进制，边平方边取模：若 $b$ 的当前最低位为 $1$ 就把底数乘入答案，然后底数自乘、$b$ 右移一位。时间 $O(\log b)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
