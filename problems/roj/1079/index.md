---
oj: "roj"
problem_id: "1079"
title: "计算分数加减表达式的值"
description: "按奇偶符号直接逐项累加交错调和级数前 n 项，输出保留 4 位小数。"
difficulty: "入门"
date: 2026-09-29 17:42
updated: 2026-10-05 00:27
toc: true
tags: ["模拟", "数学", "入门"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1079
---

[[TOC]]

## 题目描述

输入一个正整数 $n$（$1 \le n \le 1000$），求表达式 $\frac11 - \frac12 + \frac13 - \frac14 + \cdots + (-1)^{n-1}\frac1n$ 的值，其中第 $i$ 项为 $\frac1i$，奇数项取正、偶数项取负。结果保留到小数点后 $4$ 位输出，如输入 `2` 时输出 `0.5000`。

## 思路

第 $i$ 项就是 $\frac1i$ 乘上符号：奇数项加、偶数项减。从 $1$ 到 $n$ 枚举 $i$，按奇偶性把 $\pm\frac1i$ 逐项累加进浮点答案即可，复杂度 $O(n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
