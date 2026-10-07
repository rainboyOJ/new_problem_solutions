---
oj: "roj"
problem_id: "3568"
title: "[NOIP2009-普及] 多项式输出"
description: "按规则输出一元多项式：跳过零项，首项省略正号，高于 0 次且系数绝对值为 1 时省略 1。"
difficulty: "普及-"
date: 2026-10-02 08:01
updated: 2026-10-06 14:16
toc: true
tags: ["模拟", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3568
---

[[TOC]]

## 题目描述

给定一元 $n$ 次多项式降幂排列的 $n+1$ 个系数，按规则输出多项式：只保留非零项；首项正号省略、负号开头，其余项用 `+` / `-` 连接；高于 $0$ 次且系数绝对值为 $1$ 时省略系数；指数部分按次数输出 `x^b`、`x` 或空。

样例#1 输入 `5` / `100 -1 1 -3 0 10`，输出 `100x^5-x^4+x^3-3x^2+10`；样例#2 输入 `3` / `-50 0 0 1`，输出 `-50x^3+1`。

数据范围：$0 \le n \le 100$，系数绝对值 $\le 100$。

## 思路

从高次到低次扫描系数，$0$ 则跳过；用 `first` 标记是否为首项非零项，就地决定符号、系数是否省略、幂次形式并直接输出。

## 参考代码

@include-code(./main.cpp, cpp)
