---
oj: "roj"
problem_id: "1327"
title: "【例7.6】黑白棋子的移动"
description: "用数组模拟空位推进，按固定递归模式把黑白相间排列到目标局面。"
difficulty: "入门"
date: 2026-09-30 05:27
updated: 2026-10-05 09:53
toc: true
tags: ["模拟", "递归", "构造"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1327
---

[[TOC]]

## 题目描述

有 $2n$ 个棋子排成一行（$n \geqslant 4$），最初前 $n$ 个为白子 `o`，后 $n$ 个为黑子 `*`，末尾追加两个空位 `-`。每次选一对相邻棋子整体平移到空位（左右顺序不变，必须跳过若干棋子），要求输出任意一组合法移动序列，使最终局面变成黑白相间的 `o*o*…o*` 且末尾仍为两个空位。

输入一个整数 $n$，输出每一步的局面，格式为 `step k:局面`。

## 思路

按固定递归模式推进空位即可：$n > 4$ 时把第 $n, n+1$ 位的 `o*` 移到空位，再把 `**` 移到新空位，规模归约为 $n-1$；$n = 4$ 时用固定收尾序列 $\{4,8,2,7,1\}$ 收尾。每次 `move(m)` 把 `a[m],a[m+1]` 复制到空位并把空位左移回 $m$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
