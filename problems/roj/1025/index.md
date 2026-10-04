---
oj: "roj"
problem_id: "1025"
title: "保留12位小数的浮点数"
description: "读入 double 后用 printf 的 %.12f 定点格式化：按二进制精确值四舍五入到 12 位小数并补零。"
difficulty: "入门"
date: 2026-09-29 13:52
updated: 2026-10-04 22:43
toc: true
tags: ["入门", "输入输出", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1025
---

[[TOC]]

## 题目描述

读入一个双精度浮点数，保留 12 位小数输出。输入一行一个双精度浮点数，输出一行恰好 12 位小数的结果。样例输入 `3.1415926535798932`，样例输出 `3.141592653580`。

## 思路

用 `scanf("%lf")` 读入 `double`，再用 `printf("%.12f")` 输出。它按浮点数的精确二进制值四舍五入到 12 位小数，小数位不足自动补 `0`，负号也会保留；若改用 `cout << x`，小数位数与舍入都不可控。

## 参考代码

@include-code(./main.cpp, cpp)
