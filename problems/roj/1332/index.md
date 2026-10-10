---
oj: "roj"
problem_id: "1332"
title: "【例2-1】周末舞会"
description: "出队者立刻回到队尾，队伍只是整体轮转，因此第 i 支舞曲两队的出场编号就是 ((i-1) mod m)+1 与 ((i-1) mod n)+1，循环 k 次输出即可。"
difficulty: "入门"
date: 2026-09-30 05:43
updated: 2026-10-05 10:01
toc: true
tags: ["模拟", "队列", "周期", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1332
---

[[TOC]]

## 题目描述

男队 $m$ 人、女队 $n$ 人，编号为初始位置 $1..m$ 与 $1..n$。每支舞曲取两队队头各一人配成一对，配完的两人立刻回到各自队尾，共跳 $k$ 支舞曲。
输入：第一行 $m$ $n$，第二行 $k$（$m, n, k \le 100$）。输出：$k$ 行，每行为「男队编号 女队编号」。样例：输入 `4 6` 换行 `7`，输出 `1 1`、`2 2`、`3 3`、`4 4`、`1 5`、`2 6`、`3 1`。

## 思路

出队者立刻回到队尾，队伍的内容从不改变，只是整体轮转，所以第 $i$ 支舞曲两队的出场编号分别是两条循环序列 $1..m$ 与 $1..n$。
于是第 $i$ 支配对就是 $((i-1) \bmod m)+1$ 与 $((i-1) \bmod n)+1$，循环 $k$ 次直接输出，时间 $O(k)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
