---
oj: "roj"
problem_id: "1300"
title: "鸡蛋的硬度"
description: "扔鸡蛋问题：f[i][j] 为 i 层楼、j 个蛋最坏情况的最少扔蛋次数，枚举首扔位置 x，碎则测下层段且蛋减一、不碎测上层段蛋不变，max 套 min，预计算全表后每组询问 O(1) 查表。"
difficulty: "普及-"
date: 2026-09-30 03:53
updated: 2026-10-05 08:33
toc: true
tags: ["动态规划", "区间DP", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1300
---

[[TOC]]

## 题目描述

楼高 $n$ 层，手里有 $m$ 个硬度相同的鸡蛋：硬度 $x$（$0 \leqslant x \leqslant n$）满足从 $\leqslant x$ 层扔不碎（蛋可继续用）、从 $> x$ 层扔必碎。要设计一个测试方案，无论真实硬度是多少都能把它唯一确定出来，求**最坏情况下**所需的最少扔蛋次数。

输入包括多组数据，每组数据一行两个正整数 $n$ 和 $m$（$1 \leqslant n \leqslant 100$，$1 \leqslant m \leqslant 10$），分别表示楼高和蛋数；对每组数据输出一行最优策略在最坏情况下的扔蛋次数。样例输入 `100 1` / `100 2`，对应输出 `100` / `14`。

## 思路

一次扔蛋把问题切成两个更小的同类问题：在 $x$ 层扔一次，碎了剩 $x-1$ 层、$j-1$ 个蛋，不碎剩 $i-x$ 层、$j$ 个蛋，于是定义 $f[i][j]$ 为 $i$ 层楼、$j$ 个蛋最坏情况下的最少扔蛋次数，转移为 $f[i][j] = 1 + \min_x \max(f[x-1][j-1],\ f[i-x][j])$。边界是 $f[0][j]=0$、$f[i][1]=i$（单蛋只能逐层往上扔，跳层碎了就无法区分）。预计算 $O(n^2 m)$ 的全表后每组询问 $O(1)$ 查表输出。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
