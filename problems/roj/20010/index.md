---
oj: "roj"
problem_id: "20010"
title: "吊桥2"
description: "排序后每轮把最慢两只送过桥：最快往返接送与最快次快结伴两种送法取小，剩三只内直接收尾，O(n log n)。"
difficulty: "普及-"
date: 2026-10-02 19:52
updated: 2026-10-06 08:59
toc: true
tags: ["贪心", "排序", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20010
---

[[TOC]]

## 题目描述

$n$ 只史莱姆过吊桥，第 $i$ 只单独过桥耗时 $t_i$。每次最多 2 只同行，必须有人携带手电筒；该趟耗时按慢者计。一批过桥后手电筒留在对岸，需有人送回才能接下一批。求全部过桥的最短总时间。

**输入**：第一行 $n$，第二行 $n$ 个整数表示各史莱姆过桥时间。  
**输出**：一个整数，最短总时间。  
**数据范围**：$0 \le n \le 1000$，时间 $\le 100$。

样例：$n=4,\ t=[1,2,5,10]$，输出 $17$；$n=5,\ t=[1,2,8,7,6]$，输出 $22$。

## 思路

升序排序后，每轮把最慢的两只送过桥。两种送法取最小值：最快往返接送（$2a_1+a_{n-1}+a_n$）或最快与次快结伴（$a_1+2a_2+a_n$）。每轮消去 2 只，剩 3 只以内直接收尾。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
