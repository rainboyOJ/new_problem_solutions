---
oj: "roj"
problem_id: "1276"
title: "【例9.20】编辑距离"
description: "末位三选一的前缀 DP：相同取对角线，不同取删除/插入/替换三个相邻状态的 min 加一，再用滚动一维数组把空间压到 O(m)。"
difficulty: "普及-"
date: 2026-09-30 02:55
updated: 2026-10-05 07:44
toc: true
tags: ["字符串", "动态规划", "线性DP", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1276
---

[[TOC]]

## 题目描述

给定字符串 $A$ 与 $B$，每次可以对 $A$ 执行三种操作之一：删除一个字符、插入一个字符、把一个字符改成另一个字符。求把 $A$ 变成 $B$ 所需的最少操作次数（即编辑距离）。输入第一行为 $A$、第二行为 $B$，两串长度均小于 2000；输出一个整数表示最少操作次数。样例：输入 `sfdqxbw` 与 `gfdgw`，输出 `4`。

## 思路

设 $f(i,j)$ 表示把 $A$ 的前 $i$ 个字符变成 $B$ 的前 $j$ 个字符的最少操作数，则 $f(i,j)$ 只由三种收尾决定：删除 $a_i$ 对应 $f(i-1,j)$，插入 $b_j$ 对应 $f(i,j-1)$，改写 $a_i$ 为 $b_j$ 对应 $f(i-1,j-1)$（字符相同时零代价），取三者最小即可。边界为 $f(i,0)=i$、$f(0,j)=j$，答案是 $f(n,m)$。由于第 $i$ 行只依赖第 $i-1$ 行和本行左邻，可以用滚动一维数组把空间压到 $O(m)$，时间复杂度 $O(nm)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
