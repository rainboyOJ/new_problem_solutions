---
oj: "roj"
problem_id: "1085"
title: "球弹跳高度的计算"
description: "反弹高度构成公比 1/2 的等比数列，总路程=初始下落+前 9 次反弹的往返，即 3h-h/512；第 10 次反弹高 h/1024，按 6 位有效数字输出。"
difficulty: "入门"
date: 2026-09-29 18:05
updated: 2026-10-05 00:33
toc: true
tags: ["模拟", "等比数列", "浮点输出"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1085
---

[[TOC]]

## 题目描述

一球从高度 $h$（米）自由落下，每次落地后反弹回**当前**高度的一半再落下。求第 10 次落地时总共经过的米数，以及第 10 次反弹的高度。输入一个整数 $h$；输出两行：第一行为到第 10 次落地时一共经过的米数，第二行为第 10 次反弹的高度。结果可能是实数，用 `double` 保存，用 `cout << x` 或 `printf("%g", x)` 输出即可（6 位有效数字、去尾零）。

样例输入：`20`；样例输出：`59.9219` 与 `0.0195312`。

## 思路

反弹高度构成公比 $1/2$ 的等比数列 $h_i=h/2^i$。总路程 = 初始下落 $h$ + 前 9 次反弹的往返 $2h_i = 3h-h/512$；第 10 次反弹高度 $h/1024$。直接用 double 套公式即可。

## 参考代码

@include-code(./main.cpp, cpp)