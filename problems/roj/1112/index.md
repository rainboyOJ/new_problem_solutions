---
oj: "roj"
problem_id: "1112"
title: "最大值和最小值的差"
description: "一次线性扫描维护最大值和最小值，相减即得极差。"
difficulty: "入门"
date: 2026-09-29 19:27
updated: 2026-10-05 02:16
toc: true
tags: ["入门", "数组", "最值", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1112
---

[[TOC]]

## 题目描述

给定 $M$ 个整数（绝对值不超过 $10^4$，$M \leqslant 10^4$），输出最大值与最小值的差。第二行 $M$ 个整数以空格隔开。

样例：$5$ / `2 5 7 4 2`，最大值 $7$、最小值 $2$，输出 $5$。

## 思路

答案只由最大值和最小值决定，其余元素无关紧要。用第一个数初始化两个极值，再对后面每个数比较更新，最后相减即可。

## 参考代码

@include-code(./main.cpp, cpp)
