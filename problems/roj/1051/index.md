---
oj: "roj"
problem_id: "1051"
title: "分段函数"
description: "三段左闭右开区间表驱动：把（起点, 表达式）按起点排序，取起点不超过 x 的最后一段代入求值，O(1) 输出三位小数。"
difficulty: "入门"
date: 2026-09-29 16:21
updated: 2026-10-04 23:37
toc: true
tags:
  - 分支结构
  - 表驱动
  - Python
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1051
---

[[TOC]]

## 题目描述

给定实数 $x \in [0, 20)$，计算分段函数 $y = f(x)$ 的值，保留三位小数输出：$y = \begin{cases} -x + 2.5, & 0 \leqslant x < 5 \\ 2 - 1.5(x-3)^2, & 5 \leqslant x < 10 \\ \dfrac{x}{2} - 1.5, & 10 \leqslant x < 20 \end{cases}$

输入一个浮点数 $N$（$0 \leqslant N < 20$），输出对应的函数值 $f(N)$，保留三位小数。样例：输入 `1.0`，输出 `1.500`。

## 思路

三段区间左闭右开，依次判断即可：`x < 5` 走第一段，`x < 10` 走第二段，否则走第三段，端点归属由判断顺序自然保证（$x=5$、$x=10$ 都落入下一段）。求值后用 `fixed` + `setprecision(3)` 保留三位小数输出。

## 参考代码

@include-code(./main.cpp, cpp)
