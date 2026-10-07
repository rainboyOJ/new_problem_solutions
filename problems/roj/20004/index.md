---
oj: "roj"
problem_id: "20004"
title: "回旋迷宫"
description: "第 i 次行走的方向只由方向块编号 i/k 的奇偶决定，把每次位移按方向附 ± 号求和，最后对 n 取一次模即得终点，O(p)。"
difficulty: "入门"
date: 2026-10-02 19:40
updated: 2026-10-06 02:12
toc: true
tags: ["入门", "模拟", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20004
---

[[TOC]]

## 题目描述

$n$ 个门 $0,1,\dots,n-1$ 顺时针围成一圈，相邻门距离为 $1$，从门 $now$ 出发，行走 $p$ 次。第 $i$ 次沿当前方向走到与当前门距离恰为 $a_i$ 的门停下；方向每 $k$ 次行走翻转一次——第 $1\sim k$ 次顺时针、第 $k+1\sim 2k$ 次逆时针，依次递推，第一次必为顺时针。沿指定方向走距离 $d$ 的落点为 $(x\pm d)\bmod n$（$+$ 顺时针、$-$ 逆时针），$a_i\ge n$ 时多绕圈不影响落点，求终点门编号。

输入第一行 $n,p,k,now$，第二行 $p$ 个整数 $a_i$；输出一个整数表示终点门编号。所有数都是 $[0,10000)$ 内的整数。样例输入 `1000 3 2 10` / `1 3 2`，样例输出 `12`。

## 思路

第 $i$ 次行走的方向只由方向块编号 `i/k`（0 起）的奇偶决定：偶数顺时针、奇数逆时针，与位置无关。环上行走就是模 $n$ 加法，所以给每个 $a_i$ 按方向附上 $\pm$ 号求和得到总位移，输出 $(now + \text{drift}) \bmod n$ 即可，一趟 $O(p)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
