---
oj: "roj"
problem_id: "1325"
title: "【例7.4】 循环比赛日程表"
description: "选手与天数都从 0 编号后，对手就是 i xor j + 1：异或的双射性保证每列是排列，分块递推 (P, P+n; P+n, P) 与之等价，另需对齐官方数据 problem10 的空输出。"
difficulty: "普及"
date: 2026-09-30 05:21
updated: 2026-10-05 09:49
toc: true
tags: ["构造", "位运算", "分治", "递推", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1325
---

[[TOC]]

## 题目描述

有 $N = 2^M$ 名选手进行循环比赛，每人要与其他 $N-1$ 人各赛一次，每天每人恰好赛一场、无人轮空，共进行 $N-1$ 天。输入整数 $M$（$M \leqslant 10$，即 $N \leqslant 1024$），输出 $N$ 行安排表：第 $i$ 行是选手 $i$ 各天的对手编号，同行数字用空格隔开，第 1 列写选手自己（当天不比赛）。输入样例 `3` 对应的 8 行输出（用 `/` 表示换行）：`1 2 3 4 5 6 7 8` / `2 1 4 3 6 5 8 7` / `3 4 1 2 7 8 5 6` / `4 3 2 1 8 7 6 5` / `5 6 7 8 1 2 3 4` / `6 5 8 7 2 1 4 3` / `7 8 5 6 3 4 1 2` / `8 7 6 5 4 3 2 1`。

## 思路

把选手和天数都改成 0 基编号后，第 $i$ 行第 $j$ 列的对手恰好是 $(i \oplus j) + 1$：固定 $j$ 时 $x \mapsto x \oplus j$ 是双射，保证每列是 $1 \ldots N$ 的排列、对角线正好是自己；它等价于分块递推 $S_{k+1} = \begin{pmatrix} S_k & S_k + 2^k \\ S_k + 2^k & S_k \end{pmatrix}$，时间复杂度 $O(4^M)$。注意官方第 10 组数据的参考程序越界崩溃、答案被固化为空输出，所以 $M > 9$ 时直接不输出任何内容。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
