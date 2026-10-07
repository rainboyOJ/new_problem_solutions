---
oj: "roj"
problem_id: "1192"
title: "放苹果"
description: "按最后一个盘子是否为空做不重不漏二分：空则少一个盘子，非空则每个盘子各垫一个苹果，得 f(m,n)=f(m,n-1)+f(m-n,n)，记忆化求整数拆分数 p_{≤n}(m)。"
difficulty: "普及-"
date: 2026-09-29 22:50
updated: 2026-10-05 05:11
toc: true
tags: ["入门", "动态规划", "计数DP", "记忆化搜索", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1192
---

[[TOC]]

## 题目描述

把 $M$ 个同样的苹果放进 $N$ 个同样的盘子里，允许有的盘子空着，求不同的分法数 $K$；$5,1,1$ 与 $1,5,1$ 是同一种分法。输入：第一行是测试数据数目 $t$（$0 \leqslant t \leqslant 20$），以下每行两个整数 $M$ 和 $N$，以空格分开（$1 \leqslant M, N \leqslant 10$）。输出：对每组数据一行输出相应的 $K$。样例输入 `1` 与 `7 3` 对应输出 `8`。

## 思路

设 $f(m,n)$ 为 $m$ 个苹果放进 $n$ 个盘子的分法数，按最后一个盘子是否为空不重不漏地分两类：空则少一个盘子得 $f(m,n-1)$；非空则非降序下所有盘子都非空，每盘先垫一个苹果得 $f(m-n,n)$。故 $f(m,n)=f(m,n-1)+f(m-n,n)$，边界 $f(0,n)=f(m,1)=1$，$m<n$ 时多余盘子必然空着可折叠为 $f(m,m)$，记忆化递推即可。
## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
