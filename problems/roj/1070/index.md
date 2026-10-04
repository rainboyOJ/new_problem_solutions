---
oj: "roj"
problem_id: "1070"
title: "人口增长"
description: "每年人口乘 1.001，n 年后人口就是 x*1.001^n，逐年递推相乘后用 printf 的 %.4f 保留四位小数输出。"
difficulty: "入门"
date: 2026-09-29 17:27
updated: 2026-10-05 00:05
toc: true
tags: ["入门", "数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1070
---

[[TOC]]

## 题目描述

我国现有 $x$ 亿人口，按每年增长 $0.1\%$ 计算，求 $n$ 年后的人口，保留小数点后四位。
输入一行两个整数 $x, n$（$1 \leqslant x \leqslant 100$，$1 \leqslant n \leqslant 100$），输出人口数。

样例输入 `13 10`，样例输出 `13.1306`。

## 思路

“每年增长 $0.1\%$”表示每年的人口都乘以 $1.001$，所以 $n$ 年后人口为 $x \times 1.001^n$。
按年递推相乘即可，注意增长的基础是当年人口而不是最初人口；输出用 `printf("%.4f")` 保留四位小数。

## 参考代码

@include-code(./main.cpp, cpp)
