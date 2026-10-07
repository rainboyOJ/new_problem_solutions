---
oj: "roj"
problem_id: "1335"
title: "【例2-4】连通块"
description: "网格四连通 flood fill 计数黑格连通块：每遇未访问黑格开块、栈式淹没；数据行被拼成整型 token，读入需复刻评测程序的 int32 溢出语义。"
difficulty: "入门"
date: 2026-09-30 05:43
updated: 2026-10-05 10:10
toc: true
tags: ["网格", "连通块", "flood-fill", "搜索", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1335
---

[[TOC]]

## 题目描述

给定 $n \times m$ 网格（$1 \leqslant n, m \leqslant 100$），每个格子为黑（`1`）或白（`0`）。若两个黑格上下左右相邻则属于同一个**四连通黑格连通块**。求连通块个数。

**输入**：第一行 `n m`，接下来 $n$ 行每行 $m$ 个 `0`/`1`。**输出**：一行 `ans`，连通块个数。

样例 $3\times 3$：`111 / 010 / 101` 共 $3$ 块。

## 思路

外层扫全图，碰到未访问的黑格就开一个新块（块数 +1）并从它出发做栈式 flood fill 把整块淹没；入栈时立即标记，每个格子至多入栈一次，总访问量 $O(nm)$。

## 参考代码

@include-code(./main.cpp, cpp)
