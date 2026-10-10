---
oj: "roj"
problem_id: "1214"
title: "八皇后"
description: "预处理所有 92 个合法解并排序，随后 O(1) 回答每个查询。"
difficulty: "普及"
date: 2026-09-29 23:51
updated: 2026-10-05 05:42
toc: true
tags:
  - 搜索
  - 回溯
  - 位运算
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1214
---

[[TOC]]

## 题目描述

在 $8 \times 8$ 棋盘上放置 8 个皇后，使任意两个不在同一行、列或对角线上。给定 $b\ (1 \leqslant b \leqslant 92)$，输出第 $b$ 个按整数值排序的皇后串（第 $i$ 行皇后列号顺次拼接成的 8 位数）。

输入格式：第 1 行为 $n$，随后 $n$ 行每行一个 $b$。输出格式：$n$ 行对应皇后串。

样例：输入 `2 1 92`，输出 `15863724` 和 `84136275`。

## 思路

8 皇后固定且只有 92 个合法解，先按行 DFS + 位运算剪枝全部枚举，按整数值排序后数组回答每次查询。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
