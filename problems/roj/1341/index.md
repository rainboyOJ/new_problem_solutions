---
oj: "roj"
problem_id: "1341"
title: "【例题】一笔画问题"
description: "用边编号 + 链式邻接表实现迭代版 Hierholzer 求欧拉路，出栈序列逆序输出。"
difficulty: "普及"
date: 2026-09-30 06:09
updated: 2026-10-05 11:08
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1341
---

[[TOC]]

## 题目描述

一笔画的路径叫欧拉路，最后回到起点的叫欧拉回路。给定 $n$ 个点 $m$ 条边的无向图，输出任意一条欧拉路或欧拉回路。
**输入**：第一行 $n, m$，接下来 $m$ 行每行一条边的两端。**输出**：一条合法路径。
**样例**：输入 `5 5` 与边 $(1,2)(2,3)(3,4)(4,5)(5,1)$，输出 `1 5 4 3 2 1`。

## 思路

奇度点个数为 $0$ 或 $2$ 才有一笔画（本题保证有解），有奇点就从奇点出发。用 Hierholzer 算法：能走就走并压栈，栈顶无路可走时弹进出栈序列；每条边按「边编号」标记走过（按点对删边会误吞平行边），出栈序列逆序输出即为答案。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
