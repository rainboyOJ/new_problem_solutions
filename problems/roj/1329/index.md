---
oj: "roj"
problem_id: "1329"
title: "【例8.2】细胞"
description: "网格连通块计数入门题：按行扫描遇到未抹掉的非 0 数字就数一个新细胞，BFS 把整个四连通块原地抹成 0 当访问标记，每格至多入队一次。"
difficulty: "入门"
date: 2026-09-30 05:33
updated: 2026-10-05 10:01
toc: true
tags: ["搜索", "BFS", "连通块"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1329
---

[[TOC]]

## 题目描述

给定一个 $n \times m$ 的字符矩阵，元素为 `0` 到 `9`。非 `0` 的数字代表细胞；上下左右相邻（四连通，不含对角线）的细胞数字属于同一细胞，求矩阵中细胞的个数。

输入：第一行为行数 $n$ 和列数 $m$，下面为一个 $n \times m$ 的矩阵，样例如下（输出 `4`）：

```text
4 10
0234500067
1034560500
2045600671
0000000089
```

## 思路

按行扫描矩阵，遇到还没抹掉的非 `0` 格子，说明它所属的细胞尚未统计，计数加一，并从它出发做 BFS：把整个四连通块原地抹成 `0` 当访问标记（入队即抹掉，保证每格至多入队一次），避免重复计数。总时间复杂度 $O(nm)$。

## 参考代码

@include-code(./main.cpp, cpp)
