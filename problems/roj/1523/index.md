---
oj: "roj"
problem_id: "1523"
title: "「一本通 3.6 练习 2」嗅探器"
description: "把“每条 a 到 b 的路径都经过 v”转成删除判据：删掉 v 后 a 到不了 b 即为必经点，逐点做一次 DFS 连通性判定，取编号最小者。"
difficulty: "普及-"
date: 2026-09-30 15:59
updated: 2026-10-06 00:37
toc: true
tags:
  - 图论
  - 必经点
  - 连通性
  - python
favorite: false
favorite_reason: ""
categories:
  - 图论
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1523
---

[[TOC]]

## 题目描述

红军要监听蓝军两个信息中心之间交换的所有信息，嗅探器必须装在一台「中间服务器」上，使得任意一条从 $a$ 到 $b$ 的路径都经过它。输入第一行是服务器数 $n$（$1 \leqslant n \leqslant 100$），接下来若干行每行两个整数 $i, j$ 表示 $i, j$ 之间有双向连接，以 `0 0` 结束，最后一行是两个信息中心 $a, b$。输出编号最小的合法服务器编号，无解输出 `No solution`。样例中 $a=4, b=2$，输出 `1`。

## 思路

点 $v$ 是 $a$ 到 $b$ 的必经点，当且仅当删掉 $v$ 后 $a$ 到不了 $b$。于是从 1 到 $n$ 枚举候选点（跳过 $a$、$b$ 自身），每个点删掉后做一次 DFS 判连通，第一个使 $a$、$b$ 不连通的就是答案；$n \leqslant 100$，总复杂度 $O(n(n+m))$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
