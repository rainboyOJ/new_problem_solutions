---
oj: "roj"
problem_id: "1014"
title: "与圆相关的计算"
description: "按题面固定的 π=3.14159 套公式 2r、2πr、πr²，用 printf 的 %.4f 统一保留 4 位小数，常量只需定义一次。"
difficulty: "入门"
date: 2026-09-29 13:19
updated: 2026-10-04 22:30
toc: true
tags: ["输入输出", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1014
---

[[TOC]]

## 题目描述

给定圆的半径 $r$（$0 < r \leqslant 10000$），取圆周率 $\pi = 3.14159$，求圆的直径、周长、面积，每个数保留小数点后 4 位。输入一行一个实数 $r$，输出一行三个数，空格分隔，各保留 4 位小数。样例输入 `3.0`，输出 `6.0000 18.8495 28.2743`。

## 思路

直接套公式：直径 $d = 2r$，周长 $C = 2\pi r$，面积 $S = \pi r^2$。$\pi$ 必须用题面钦定的 $3.14159$，换成更高精度的常量会让第 4 位与样例不符。输出用 `printf("%.4f")` 保留 4 位小数即可。

## 参考代码

@include-code(./main.cpp, cpp)
