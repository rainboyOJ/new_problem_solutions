---
oj: "roj"
problem_id: "1156"
title: "求π的值"
description: "用格雷戈里级数在 x=1/√3 处逐项累加 arctan：分子每步乘 -x² 递推、分母取奇数，整项绝对值首次小于 1e-6 时停止，结果乘 6 输出。"
difficulty: "入门"
date: 2026-09-29 21:15
updated: 2026-10-05 03:50
toc: true
tags: ["入门", "数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1156
---

[[TOC]]

## 题目描述

利用 $\arctanx(x) = x - \frac{x^3}{3} + \frac{x^5}{5} - \frac{x^7}{7} + \cdots$ 和恒等式 $\pi = 6\arctanx(\frac{1}{\sqrt 3})$，逐项累加级数求 $\arctanx(\frac{1}{\sqrt 3})$：当最后一项的绝对值小于 $10^{-6}$ 时停止，把部分和乘 $6$ 得到 $\pi$ 的近似值。

- 输入：无。
- 输出：$\pi$ 的值，保留到小数点后 $10$ 位。

## 思路

相邻两项的分子比值恒为 $-x^2$，一个乘法同时完成升幂和变号；分母从 $1$ 起每次加 $2$。停止条件要比较含分母系数的整项 $\left|\frac{x^{2k+1}}{2k+1}\right|$（而非分子），首次小于 $10^{-6}$ 的那一项不再累加，最后乘 $6$ 输出 $10$ 位小数。

## 参考代码

@include-code(./main.cpp, cpp)
