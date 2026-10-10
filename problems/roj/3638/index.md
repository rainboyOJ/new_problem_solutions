---
oj: "roj"
problem_id: "3638"
title: "[noip2016-提高] 玩具谜题"
description: "把朝向与左右折算成下标 ±1，每条指令模 n 直接跳 s 步，O(n+m) 环形模拟。"
difficulty: "普及-"
date: 2026-10-02 12:08
updated: 2026-10-06 15:51
toc: true
tags: ["模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3638
---

[[TOC]]

## 题目描述

n 个玩具小人围成一圈，逆时针顺序给出朝向（0 朝内、1 朝外）和职业。从第 1 个小人出发，依次执行 m 条指令：a=0 向左数 s 个，a=1 向右数 s 个，求到达的小人职业。1≤n,m≤1e5，1≤s<n。

## 思路

朝向与左右共同决定移动方向：a 与当前朝向相异则沿逆时针（下标 +1），相同则顺时针（下标 -1）。环上移动 s 步等价于 `(pos ± s) mod n`，每条指令 O(1)。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
