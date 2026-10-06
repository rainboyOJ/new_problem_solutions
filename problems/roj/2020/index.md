---
oj: "roj"
problem_id: "2020"
title: "usaco-1.5.4 跳棋的挑战"
description: "N 皇后搜索：逐行放置，用列与两条对角线的位掩码 O(1) 判冲突，按列号升序展开保证字典序，输出前 3 个解与总解数。"
difficulty: "普及-"
date: 2026-10-01 03:20
updated: 2026-10-06 09:41
toc: true
tags: ["搜索", "回溯", "位运算", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2020
---

[[TOC]]

## 题目描述

在 $N \times N$ 的棋盘上放 $N$ 个棋子，要求每行、每列、每条对角线上至多一个棋子。用序列 $c_1 \dots c_N$ 表示解，$c_i$ 为第 $i$ 行棋子所在列号。按字典序输出前 3 个解，最后一行输出解的总数。$6 \le N \le 13$。

输入：一个整数 $N$。  
输出：前三行各为一个解，数字间用空格隔开；第四行为解的总数。

样例输入 `6` 的样例输出：
```
2 4 6 1 3 5
3 6 2 5 1 4
4 1 5 2 6 3
4
```

## 思路

逐行 DFS 放置棋子，用三个整数位掩码分别记录已占用的列、主对角线（$r+c$）、副对角线（$r-c$）。下一行时主对角线掩码左移一位、副对角线掩码右移一位，再用 `free & -free` 取最小合法列，天然按字典序搜索。到达第 $N$ 行时保存前 3 个解并统计总数。

## 参考代码

@include-code(./main.cpp, cpp)
