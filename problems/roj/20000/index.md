---
oj: "roj"
problem_id: "20000"
title: "艰难的第一天"
description: "等比数列首次越过 4096MB 阈值的分钟数：取对数化为闭式上取整，再用精确乘法修正临界。"
difficulty: "入门"
date: 2026-10-02 19:16
updated: 2026-10-06 02:06
toc: true
tags: ["入门", "数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20000
---

[[TOC]]

## 题目描述

病毒第 1 分钟占用 $x$ MB，之后每分钟占用量变为上一分钟的 $y$ 倍；内存剩余 $4\text{GB}=4096\text{MB}$，占用量**等于** 4096 就算占满，求第几分钟占满。
输入一行两个实数 $x,\ y$（$0<x\leqslant 1000,\ 1<y\leqslant 10$），输出一个整数表示分钟数。
样例：输入 `32 2` 输出 `8`；输入 `2 1.5` 输出 `20`。

## 思路

第 $n$ 分钟占用量为 $x\cdot y^{\,n-1}$，要求最小 $n$ 使 $x\cdot y^{\,n-1}\geqslant 4096$；两边取对数得 $n-1\geqslant \ln(4096/x)/\ln y$，上取整再 $+1$ 即为答案。浮点对数只当估计，再用高精度乘法在估计值附近双向修正，保证“恰好等于 4096 即占满”的临界判对。

## 参考代码

@include-code(./main.cpp, cpp)
