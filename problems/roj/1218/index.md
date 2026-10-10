---
oj: "roj"
problem_id: "1218"
title: "取石子游戏"
description: "Euclid 博弈：商 ⌊a/b⌋ ≥ 2 或整除时执子者必胜，商为 1 时取法唯一、胜负随轮次翻转，辗转相除 O(log V) 模拟到首个可胜局面即可。"
difficulty: "普及-"
date: 2026-09-30 00:03
updated: 2026-10-05 05:50
toc: true
tags: ["博弈论", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1218
---

[[TOC]]

## 题目描述

有两堆石子，两人轮流取；每次只能从较多的一堆取，取的数量必须是较少一堆的整数倍。把任意一堆取空者获胜。多组输入，每行两个正整数 $a,b$，以 `0 0` 结束。

## 思路

设 $a \ge b$。若 $b \mid a$ 或 $\lfloor a/b \rfloor \ge 2$，当前执子者必胜；否则唯一变为 $(b,a-b)$ 且胜负翻转，沿辗转相除链走到首个可胜局面看轮到谁。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
