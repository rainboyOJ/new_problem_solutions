---
oj: "roj"
problem_id: "3618"
title: "[NOIP2014]生活大爆炸版石头剪刀布"
description: "把五手势胜负关系预编译成查表，两人按各自周期取模逐轮判胜计分，O(N) 模拟出全部 N 轮得分。"
difficulty: "入门"
date: 2026-10-02 10:54
updated: 2026-10-06 15:14
toc: true
tags: ["入门", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3618
---

[[TOC]]

## 题目描述

甲、乙两人玩升级版石头剪刀布：手势 $0$ 剪刀、$1$ 石头、$2$ 布、$3$ 蜥蜴人、$4$ 斯波克，每种手势恰好胜两种、负两种，每轮胜者得 $1$ 分、平局不得分。两人分别按周期 $N_A$、$N_B$ 循环出拳，第 $r$ 轮（从 $0$ 计）甲出 $a_{r \bmod N_A}$、乙出 $b_{r \bmod N_B}$，共 $N$ 轮。输入第一行 $N,N_A,N_B$，第二、三行分别为两人的周期序列；输出甲、乙两人的总得分。$0<N,N_A,N_B\le 200$。

样例输入：`10 5 6` / `0 1 2 3 4` / `0 3 4 2 1 0`，输出 `6 2`。

## 思路

把 $10$ 对胜负关系预存成表，每轮用 $r \bmod N_A$、$r \bmod N_B$ 取出双方手势查表判胜，胜者计一分即可。$N\le 200$，直接 $O(N)$ 模拟。

## 参考代码

@include-code(./main.cpp, cpp)
