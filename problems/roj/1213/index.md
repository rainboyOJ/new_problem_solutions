---
oj: "roj"
problem_id: "1213"
title: "八皇后问题"
description: "逐列回溯放皇后，用 row[c] 记录每列皇后的行号，落子前检查同行与两条对角线冲突，按列优先、行号升序的顺序输出全部 92 个解。"
difficulty: "普及-"
date: 2026-09-29 23:53
updated: 2026-10-05 05:42
toc: true
tags:
  - 搜索
  - 回溯
  - 位运算
  - python
favorite: false
favorite_reason: ""
categories:
  - 搜索
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1213
---

[[TOC]]

## 题目描述

在 $8 \times 8$ 的国际象棋棋盘上放置 8 个皇后，要求任意两个皇后不在同一行、同一列或同一条对角线上，输出全部 92 个解。输入为空。对每个解先输出一行 `No. k`（k 从 1 开始连续编号），再输出 8 行棋盘：第 r 行第 c 列为 `1` 当且仅当第 c 列的皇后放在第 r 行，每个数后跟一个空格。按"逐列放置、每列行号从小到大"的搜索顺序输出（见样例）。

## 思路

逐列回溯：每列按行号 0..7 枚举，用一个 `row[c]` 数组记录第 c 列皇后所在行，落子前检查与前 c 列是否同行或在同一条对角线上（行差等于列差即冲突），放满 8 列就按格式输出。枚举顺序天然是"列优先、每列行号升序"，与题目要求一致。

## 参考代码

@include-code(./main.cpp, cpp)
