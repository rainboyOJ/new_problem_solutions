---
oj: "roj"
problem_id: "1110"
title: "查找特定的值"
description: "无序序列线性扫描，找到目标值第一次出现的位置并输出下标，未找到输出 -1。"
difficulty: "入门"
date: 2026-09-29 19:14
updated: 2026-10-05 01:41
toc: true
tags: ["线性查找", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1110
---

[[TOC]]

## 题目描述

在一个下标从 $1$ 开始的序列中查找给定值，输出它第一次出现的位置。输入三行：第一行为序列长度 $n$（$1 \leqslant n \leqslant 10000$）；第二行为 $n$ 个绝对值不超过 $10000$ 的整数；第三行为待查找的整数 $x$（$|x| \leqslant 10000$）。输出 $x$ 第一次出现的下标，若不存在则输出 `-1`。
样例输入 `5`、`2 3 6 7 3`、`3`，输出 `2`。

## 思路

序列无序，不能二分，只能从左到右线性扫描：遇到的第一个等于 $x$ 的元素下标就是答案，扫完仍未命中则输出 `-1`；注意下标从 $1$ 开始、命中后立即停止，复杂度 $O(n)$。

## 参考代码

@include-code(./main.cpp, cpp)
