---
oj: "roj"
problem_id: "1101"
title: "不定方程求解"
description: "枚举 x 的非负上界 c//a，逐个判定 (c-ax) 能否被 b 整除，整除即唯一确定一组非负解，计数即为答案。"
difficulty: "入门"
date: 2026-09-29 18:51
updated: 2026-10-05 01:08
toc: true
tags:
  - 枚举
  - 数论
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1101
---

[[TOC]]

## 题目描述

给定正整数 $a, b, c$，求不定方程 $ax + by = c$ 关于未知数 $x$ 和 $y$ 的所有非负整数解组数。

**输入**：一行三个正整数 $a, b, c$（每个 $\leqslant 1000$），空格分隔。

**输出**：一个整数，即非负整数解的组数。

**样例输入**：`2 3 18`　　**样例输出**：`4`

## 思路

固定 $x$ 后 $y = (c - ax)/b$ 被唯一确定，故只需枚举 $x \in [0, \lfloor c/a \rfloor]$，逐个判 $(c - ax) \bmod b = 0$，成立即贡献一组解；总枚举量 $\leqslant 1001$，时间复杂度 $O(c/a)$。

## 参考代码

@include-code(./main.cpp, cpp)
