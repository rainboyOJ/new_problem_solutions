---
oj: "roj"
problem_id: "1256"
title: "献给阿尔吉侬的花束"
description: "把迷宫看作无权图，从 S 出发做一次 BFS，首次到达 E 的步数即为最短时间；若 E 不可达则输出 oop!。"
difficulty: "入门"
date: 2026-09-30 02:01
updated: 2026-10-05 07:12
toc: true
tags:
  - BFS
  - 网格最短路
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1256
---

[[TOC]]

## 题目描述

阿尔吉侬要从 `S` 走到 `E`，$R\times C$ 网格上 `.` 可走、`#` 为墙，每步上下左右走一格，求最少步数，不可达输出 `oop!`。$1\le T\le 10$，$2\le R,C\le 200$，每组恰有一个 `S` 和 `E`。样例（输入→输出）：

```
3 / 3 4 / .S.. / ###. / ..E. / 3 4 / .S.. / .E.. / .... / 3 4 / .S.. / #### / ..E. → 5 / 1 / oop!
```

## 思路

把每个可达格子看成一个点，相邻可达格点连边权 1，从 `S` 做 BFS，首次到达 `E` 的层数即为最少步数；队列空仍未到 `E` 则输出 `oop!`。

## 参考代码

@include-code(./main.cpp, cpp)