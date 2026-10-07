---
oj: "roj"
problem_id: "1547"
title: "「一本通 4.3 例 1」区间和"
description: "单点加与区间求和交替：树状数组按 lowbit 把前缀和拆成 O(log n) 段，查询两次前缀和相减、修改沿链上跳，初值正序推贡献 O(n) 建树，总 O(n + m log n)。"
difficulty: "普及-"
date: 2026-09-30 17:55
updated: 2026-10-06 00:50
toc: true
tags: ["树状数组", "前缀和", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1547
---
[[TOC]]
## 题目描述
给定长度为 $n$ 的数列与 $m$ 个操作，操作分两类：`k=1 a b` 表示把 $a$ 处数字加上 $b$；`k=2 a b` 表示询问区间 $[a,b]$ 内所有数的和。输入第一行是 $n, m$（$n \le 100000$，$m \le 500000$），第二行 $n$ 个整数为数列初值，随后 $m$ 行每行三个正整数 $k, a, b$（$1 \le a \le b \le n$）。对每个询问输出对应答案。例如初值 `1 2 3 4`，依次执行 `1 3 10`、`2 1 3`、`2 2 4`，输出为 `16`、`19`。
## 思路
单点加 + 区间和用树状数组：$tree[i]$ 管辖 $(i-\mathrm{lowbit}(i), i]$，查询沿 $i \mathrel{-}= \mathrm{lowbit}(i)$ 把前缀拆成 $O(\log n)$ 段、修改沿 $i \mathrel{+}= \mathrm{lowbit}(i)$ 上跳更新，区间和即两次前缀和相减；建树按 $i=1..n$ 正序把段和推给父结点 $i+\mathrm{lowbit}(i)$，一趟 $O(n)$ 完成。真实数据 $n, m$ 可达 $10^6$，区间和会超 int，须用 `ll`。
## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
