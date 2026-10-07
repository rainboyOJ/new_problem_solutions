---
oj: "roj"
problem_id: "2023"
title: "三值的排序"
description: "按数字个数划分目标区间，贪心做两两直接对换，剩余三元环每个花两次交换，求最少交换次数。"
difficulty: "普及-"
date: 2026-10-01 03:19
updated: 2026-10-06 09:46
toc: true
tags:
  - "贪心"
  - "置换"
favorite: false
favorite_reason: ""
categories:
  - "基础算法"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2023
---

[[TOC]]

## 题目描述

给定一个长度为 $N$（$1 \le N \le 1000$）的序列，每个元素只可能是 $1$、$2$ 或 $3$。每次操作可以任选两个下标交换它们的值，求把序列排成升序所需的最少交换次数。

输入：第一行一个整数 $N$；接下来 $N$ 行每行一个数字。输出：一行一个整数，表示最少交换次数。

样例输入：第一行 `9`，后面依次 `2 2 1 3 3 3 2 3 1`（每行一个数）；样例输出：`4`。

## 思路

设 $1,2,3$ 的个数为 $c_1,c_2,c_3$，排序后的目标区间随之确定，用 $cnt(i,j)$ 表示目标区间 $i$ 的位置上实际放着数字 $j$ 的个数。先做两两直接对换：区间 $i$ 与 $j$ 之间 $\min(cnt(i,j),cnt(j,i))$ 次，每次让两个数同时归位；剩余错位必然构成三元环，每个环需 $2$ 次交换，个数为 $cnt(1,2)-d_{12}$ 与 $cnt(2,1)-d_{12}$ 中非零的那一个，答案即两组对换数之和加 $2\times$ 三元环个数。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
