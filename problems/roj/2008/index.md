---
oj: "roj"
problem_id: "2008"
title: "双重回文数"
description: "从 S+1 开始逐个向上枚举，短除法取余得到各进制数码并判断回文，统计 2~10 进制中回文次数不少于 2 的数，取前 N 个输出。"
difficulty: "入门"
date: 2026-10-01 02:42
updated: 2026-10-06 09:25
toc: true
tags: ["入门", "枚举", "进制转换", "回文数", "usaco", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2008
---

[[TOC]]

## 题目描述

若一个数从左往右读与从右往左读相同，且首尾非零，则称它为回文数。有些数在十进制下不是回文，在其它进制下却是回文。

给定 $N\ (1 \le N \le 15)$ 和 $S\ (0 < S < 10000)$，找出大于 $S$、且在二进制到十进制中至少有两种进制下为回文数的前 $N$ 个整数，按升序每行输出一个。

样例：输入 `3 25`，输出 `26`、`27`、`28`。

## 思路

从 $S+1$ 开始升序枚举每个整数，对每个候选数在 $2\sim10$ 进制分别用短除法取余得到数码串，再判断是否为回文；回文进制数达到 2 个即输出，累计输出 $N$ 个后停止。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
