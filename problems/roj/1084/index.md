---
oj: "roj"
problem_id: "1084"
title: "幂的末尾"
description: "每次乘 a 后保留末三位，迭代 b 次后格式化输出。"
difficulty: "入门"
date: 2026-09-29 17:53
updated: 2026-10-05 00:34
toc: true
tags: ["模拟", "取模"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1084
---

[[TOC]]

## 题目描述

给定两个正整数 $a, b$，求 $a^b$ 的末三位，不足三位时前补 `0`。数据范围：$1 \leqslant a \leqslant 100,\ 1 \leqslant b \leqslant 10000$。

## 思路

利用同余性质，每次把当前结果乘 $a$ 再对 $1000$ 取模，这样始终只保留末三位。迭代 $b$ 次后格式化输出即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
