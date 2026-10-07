---
oj: "roj"
problem_id: "1369"
title: "合并果子"
description: "哈夫曼思想的贪心：每次用小根堆取出最小的两堆合并，n-1 次合并的总体力最小。"
difficulty: "普及-"
date: 2026-09-30 07:28
updated: 2026-10-05 12:13
toc: true
tags: ["贪心", "堆", "哈夫曼"]
favorite: false
favorite_reason: ""
categories: ["贪心"]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1369
---

[[TOC]]

## 题目描述

$n$ 堆果子，第 $i$ 堆重量为 $a_i$。每次合并两堆，体力为两堆重量之和；合并 $n-1$ 次后只剩一堆。求最小总体力。

**输入**：第一行 $n$（$1 \le n \le 30000$），第二行 $n$ 个整数 $a_i$（$1 \le a_i \le 20000$）。  
**输出**：最小体力耗费值。

样例输入：
```
3
1 2 9
```
样例输出：
```
15
```

## 思路

每次合并的代价会作为新堆重量继续参与后续合并，因此越小的堆越早合并越优。用小根堆维护当前所有堆，每次取出最小的两堆合并，累加代价并把新堆放回，重复 $n-1$ 次即可。

## 参考代码

@include-code(./main.cpp, cpp)

