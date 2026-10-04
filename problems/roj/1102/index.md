---
oj: "roj"
problem_id: "1102"
title: "与指定数字相同的数的个数"
description: "线性扫描序列，统计等于指定数字 m 的元素个数。"
difficulty: "入门"
date: 2026-09-29 18:53
updated: 2026-10-05 01:08
toc: true
tags: ["枚举", "入门"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1102"
---

[[TOC]]

## 题目描述

给定长度为 $N$（$N \leqslant 100$）的整数序列 $a_1, \dots, a_N$ 和一个整数 $m$，求序列中与 $m$ 相同的数的个数。
输入共三行：第一行为 $N$；第二行为 $N$ 个以空格分开的整数；第三行为指定的整数 $m$。输出一个整数表示答案。
样例：输入 `3`、`2 3 2`、`2` 三行，输出 `2`。

## 思路

每个数都必须被检查一次，因此直接遍历整个序列，用计数器统计等于 $m$ 的元素个数即可，复杂度 $O(N)$。

## 参考代码

@include-code(./main.cpp, cpp)
