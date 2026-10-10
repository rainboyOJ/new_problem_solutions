---
oj: "roj"
problem_id: "1167"
title: "再求f(x,n)"
description: "按题面给出的连分式递归定义直接计算 f(x,n)，保留两位小数。"
difficulty: "入门"
date: 2026-09-29 21:39
updated: 2026-10-05 04:05
toc: true
tags: ["递归", "连分式", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1167"
---

[[TOC]]

## 题目描述

给定 $x$、$n$，函数定义为 $f(x,1)=\dfrac{x}{1+x}$，$f(x,n)=\dfrac{x}{n+f(x,n-1)}\ (n>1)$，求 $f(x,n)$ 并保留两位小数。输入两个数 $x$、$n$（$n\leqslant 9$），输出函数值。

样例输入 `1 2`，样例输出 `0.40`。

## 思路

把题面的递归式直接写成递归函数：$n=1$ 时返回 $\dfrac{x}{1+x}$，否则返回 $\dfrac{x}{n+f(x,n-1)}$。数据范围很小，递归深度安全，最后按两位小数输出即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
