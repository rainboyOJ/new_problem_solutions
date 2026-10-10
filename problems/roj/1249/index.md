---
oj: "roj"
problem_id: "1249"
title: "Lake Counting"
description: "八连通洪泛填充：扫描棋盘遇到未访问的 W 就计数，并用迭代栈把它所在整片连通水洼就地从 W 改写成 .。"
difficulty: "普及-"
date: 2026-09-30 01:45
updated: 2026-10-05 06:54
toc: true
tags: ["搜索", "洪泛填充", "连通块", "网格", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1249
---

[[TOC]]

## 题目描述

给定 $N\times M$ 的棋盘，`W` 表示有水、`.` 表示干燥，八连通（上下、左右及四条对角线）的 `W` 属于同一片水洼，求水洼总数。输入第一行 $N,M$（$1\le N,M\le110$），其后 $N$ 行为棋盘，输出水洼数。样例输入为 `10 12` 后接 $10$ 行棋盘，样例输出 `3`。

## 思路

八连通不是四连通，斜着相邻也算同一片。外层扫描棋盘，每遇到一个仍为 `W` 的格子就说明发现一片新水洼：答案加一，再从它出发用迭代栈洪泛，把整片连通水洼全部改写成 `.`，棋盘因此兼任访问标记。总复杂度 $O(NM)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
