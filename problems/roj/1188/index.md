---
oj: "roj"
problem_id: "1188"
title: "菲波那契数列(2)"
description: "多组询问共享同一个数列：一次线性递推把斐波那契尾三位预计算到 max(a)，之后每问 O(1) 查表。"
difficulty: "入门"
date: 2026-09-29 22:38
updated: 2026-10-05 04:48
toc: true
tags: ["入门", "递推", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1188
---

[[TOC]]

## 题目描述

菲波那契数列：$f(1) = f(2) = 1$，$f(i) = f(i-1) + f(i-2)$（$i \geqslant 3$）。

第一行是组数 $n$，后面 $n$ 行每行一个正整数 $a$（$1 \leqslant a \leqslant 10^6$），对每个 $a$ 输出 $f(a) \bmod 1000$。

样例输入（每组一行）：`4 5 2 19 1`，样例输出：`5 1 181 1`。

## 思路

多组询问共享同一个数列：先一次线性递推到 $\max a$，把每个 $f(i) \bmod 1000$ 存进全局数组，之后每问 $O(1)$ 查表。同余对加法封闭，边算边取模不影响结果。总复杂度 $O(\max a + n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
