---
oj: "roj"
problem_id: "1261"
title: "【例9.5】城市交通网络"
description: "DAG 最短路：边只从小城市指向大城市，编号即拓扑序，逆序 DP f(i)=min(w(i,j)+f(j)) 并用 go 数组回溯，O(N²) 求 1→N 最小费用与路径。"
difficulty: "普及-"
date: 2026-09-30 02:15
updated: 2026-10-05 07:19
toc: true
tags: ["动态规划", "图论", "最短路", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1261
---

[[TOC]]

## 题目描述

有 $N$（$N \leqslant 20$）个城市，单向路网中所有道路都从编号小的城市通向编号大的城市。给出 $N \times N$ 的费用矩阵 $w_{i,j}$（0 表示两点间没有直通道路），求城市 1 到城市 $N$ 的最小总费用及经过的城市序列。输入第一行一个整数 $N$，随后 $N$ 行每行 $N$ 个数构成费用矩阵；输出两行，第一行 `minlong=最小费用`，第二行是路径上依次经过的城市编号（空格分隔）。样例：输入 `10` 及 10×10 矩阵（$w_{1,2}=2,\ w_{1,3}=5,\ w_{1,4}=1,\ w_{3,5}=6,\ w_{5,8}=3,\ w_{8,10}=5$ 等），输出 `minlong=19` 与 `1 3 5 8 10`。

## 思路

所有边都从小编号指向大编号，编号本身就是拓扑序，于是从 $N-1$ 倒推到 1 做逆拓扑序 DP：$f(N)=0$，$f(i)=\min\limits_{w_{i,j}\neq 0}\bigl(w_{i,j}+f(j)\bigr)$，其中 $f(i)$ 表示从 $i$ 到 $N$ 的最小费用。用 `go[i]` 记下取得最小值的后继，答案 $f(1)$，再从 1 沿 `go` 回溯即得路径。总转移次数 $O(N^2)$。

## 参考代码

@include-code(./main.cpp, cpp)
