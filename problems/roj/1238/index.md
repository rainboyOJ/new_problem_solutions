---
oj: "roj"
problem_id: "1238"
title: "一元三次方程求解"
description: "利用根是两位小数且两根之差至少为 1 的约定，在 [-100,100] 上以 0.01 步长从左到右扫描，命中 |f(x)|≤1e-5 的网格点即根，三次命中天然有序。"
difficulty: "入门"
date: 2026-09-30 01:09
updated: 2026-10-05 06:24
toc: true
tags: ["枚举", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1238
---

[[TOC]]

## 题目描述

给定实系数 $a,b,c,d$，求解方程 $ax^3+bx^2+cx+d=0$。约定存在三个不同实根，根在 $[-100,100]$ 内且任意两根之差的绝对值 $\geqslant 1$。输入一行四个实数，输出一行三个实根，按从小到大顺序，精确到小数点后 $2$ 位。

## 思路

根都是两位小数，因此在 $[-100,100]$ 上以 $0.01$ 为步长从左到右扫描，用秦九韶形式计算 $f(x)$，遇到 $|f(x)|\leqslant 10^{-5}$ 即记录为根并继续向右找下一个。根间距 $\geqslant 1$ 保证不会漏或重。

## 参考代码

@include-code(./main.cpp, cpp)
