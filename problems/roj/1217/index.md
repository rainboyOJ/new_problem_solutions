---
oj: "roj"
problem_id: "1217"
title: "棋盘问题"
description: "棋盘上放 k 枚互不同行同列的棋子：逐行决策并把列占用压成 n 位掩码，记忆化搜索 O(n²·2ⁿ) 计数。"
difficulty: "普及-"
date: 2026-09-30 00:02
updated: 2026-10-05 05:50
toc: true
tags:
  - 搜索
  - 递归
  - 位运算
favorite: false
favorite_reason: ""
categories:
  - 搜索
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1217
---

[[TOC]]

## 题目描述

在一个给定形状的 $n \times n$ 棋盘（形状可能不规则）上摆放棋子，棋子没有区别。要求任意两个棋子不在同一行或同一列，求摆放 $k$ 个棋子的可行方案数 $C$。

输入含多组数据：每组第一行是两个正整数 $n, k$（$n \leqslant 8$，$k \leqslant n$），随后 $n$ 行每行 $n$ 个字符，`#` 表示棋盘区域、`.` 表示空白区域；以 `-1 -1` 结束输入。对每组数据输出一行方案数 $C$（保证 $C < 2^{31}$）。样例：棋盘 `#.`/`.#`、$k=1$ 时输出 `2`；棋盘 `...#`/`..#.`/`.#..`/`#...`、$k=4$ 时输出 `1`。

## 思路

按行决策让"互不同行"自动成立：每行只有"不放"和"在某一列放一枚"两种选择。处理到第 $row$ 行时，未来只取决于哪些列已被占用，于是把列占用压成 $n$ 位掩码 $used$（已放枚数即 $used$ 中 1 的个数），记忆化搜索 $count(row, used) = count(row+1, used) + \sum_{c \text{ 可放且空闲}} count(row+1, used \cup \{c\})$。剪枝：$used$ 已有 $k$ 个 1 时记 1 种方案，剩余行数 $n - row$ 小于还差枚数时记 0，总复杂度 $O(n^2 \cdot 2^n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
