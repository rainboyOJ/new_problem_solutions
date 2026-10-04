---
oj: "roj"
problem_id: "1173"
title: "阶乘和"
description: "滚动维护阶乘并高精度累加 1! 到 n! 的和。"
difficulty: "普及-"
date: 2026-09-29 22:03
updated: 2026-10-05 04:18
toc: true
tags: ["高精度", "数学", "递推", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1173
---

[[TOC]]

## 题目描述

计算 $S=1!+2!+\dots+n!$（$n\le 50$），输入正整数 $n$，输出精确结果 $S$。

输入格式：一个正整数 $n$。

输出格式：一个整数 $S$。

样例输入：`5`，样例输出：`153`。

## 思路

滚动维护当前阶乘 $f_i=f_{i-1}\times i$，再累加到答案中；$n\le 50$ 时结果超过 64 位整数范围，故用数组实现十进制高精度乘与加。

## 参考代码

@include-code(./main.cpp, cpp)
