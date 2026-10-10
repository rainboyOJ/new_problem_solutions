---
oj: "roj"
problem_id: "1577"
title: "「一本通 5.2 例 3」数字转换"
description: "真约数和小于自身就与它连一条无向边，可证建出的图是森林：最多变换步数就是树的直径，筛法建图后每棵树两次 BFS 求直径取最大。"
difficulty: "普及-"
date: 2026-09-30 19:46
updated: 2026-10-06 00:48
toc: true
tags: ["图论", "树", "数论", "筛法", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1577
---

[[TOC]]

## 题目描述

给定正整数 $n$。若数 $x$ 的真约数和 $y$ 满足 $y < x$，则 $x$ 与 $y$ 可以互相变换（双向）。所有变换数字必须在 $1 \sim n$ 范围内。求不断变换且不出现重复数字的最多变换步数。

**输入**：一个正整数 $n$。  
**输出**：最多变换步数。  
**样例输入**：`7`  
**样例输出**：`3`（路线 $4 \to 3 \to 1 \to 7$）  
数据范围：$1 \le n \le 50000$。

## 思路

$s(x) < x$ 时把 $x$ 与 $s(x)$ 连无向边，可证图中无环，形成森林。树上不重复路径即树直径，每棵树两次 BFS 求直径取最大。真约数和用倍数筛 $O(n \log n)$ 预处理。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
