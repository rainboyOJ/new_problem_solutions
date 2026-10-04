---
oj: "roj"
problem_id: "1124"
title: "矩阵加法"
description: "逐行读入两个矩阵，用双重循环对应位置相加后输出，时间复杂度 O(nm)。"
difficulty: "入门"
date: 2026-09-29 19:50
updated: 2026-10-05 02:40
toc: true
tags: ["入门", "输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1124
---

[[TOC]]

## 题目描述

输入两个 $n$ 行 $m$ 列的矩阵 $A$、$B$（$1 \le n,m \le 100$，元素 $1 \sim 1000$），输出 $C=A+B$。先输入 $n,m$，随后 $A$ 的 $n$ 行、$B$ 的 $n$ 行，每行 $m$ 个整数；输出 $C$ 的 $n$ 行，每行 $m$ 个整数，对应位置相加，相邻数字间单个空格。样例 $3\times3$ 输出为 `2 4 6` / `5 7 9` / `8 10 12`。

## 思路

按行读入两个矩阵，用双重循环逐位相加后输出，时间复杂度 $O(nm)$。

## 参考代码

@include-code(./main.cpp, cpp)
