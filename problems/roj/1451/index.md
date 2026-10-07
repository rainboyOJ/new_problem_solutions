---
oj: "roj"
problem_id: "1451"
title: "「一本通 1.4 练习 1」棋盘游戏"
description: "把 4×4 棋盘编码成 16 位掩码，相邻异色交换即两位同时翻转，在有限状态上跑 BFS 求最少步数。"
difficulty: "普及"
date: 2026-09-30 11:24
updated: 2026-10-05 23:56
toc: true
tags:
  - BFS
  - 状态压缩
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1451
---

[[TOC]]

## 题目描述

4×4 棋盘上有 8 个黑棋（1）和 8 个白棋（0），每次可交换一对有公共边的相邻棋子。给出初始局面和目标局面（各为 4 行 01 串，中间空一行），求最少移动步数。

输入共 8 行 01 串，前 4 行为初始棋盘，后 4 行为目标棋盘，每行 4 个 0/1 数字；输出一行整数表示最少步数。

## 思路

局面总数为 C(16,8)=12870。把棋盘编码成 16 位整数，相邻异色交换等价于两位同时翻转，在状态图上跑 BFS 即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
