---
oj: "luogu"
problem_id: "P1090"
title: "[NOIP 2004 提高组] 合并果子"
description: "每次合并当前最小的两堆果子，等价于构造 Huffman 树，用 Python 的 heapq 维护小根堆。"
difficulty: "普及/提高-"
date: 2026-06-21 12:34
toc: true
tags: ["贪心", "堆", "优先队列", "哈夫曼编码", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1090
---

[[TOC]]

### 题意

有 `n` 堆果子，每次选两堆合并，消耗体力等于这两堆重量之和。问怎样安排合并顺序，才能让总消耗最小。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

暴力会枚举下一次合并哪两堆，状态数增长很快，只适合小数据。

关键结论是：每次都合并当前最小的两堆，一定存在最优解。任意合并方案都可以看成一棵二叉合并树，叶子是原来的果子堆；某堆果子的重量会被累计多少次，取决于它在树中的深度。越深的叶子会被加得越多，所以重量小的果子更适合放到更深的位置。

在最优合并树里，最深的两个叶子可以看成兄弟。如果这两个位置不是当前最小的两堆，把最小的两堆换过去不会让总代价变大。因此第一步可以先合并最小的两堆，合并后把新堆当成一个整体，继续做同样的问题。

实现时维护一个小根堆：

1. 把所有果子堆放进堆；
2. 每次弹出两个最小值；
3. 把它们的和加入答案，再压回堆；
4. 重复到只剩一堆。

### Python 知识

- `heapq.heapify(heap)` 可以把列表原地变成小根堆。
- `heapq.heappop` 每次弹出当前最小值，`heapq.heappush` 把新堆放回去。
- 本题输入全是整数，换行没有特殊含义，适合用 `sys.stdin.buffer.read().split()` 一次读完。

C++ 中常用 `priority_queue<int, vector<int>, greater<int>>` 表示小根堆；Python 直接用 `heapq` 操作普通列表即可。

### 代码

@include-code(./main.py, python)

### 复杂度

一共合并 `n-1` 次，每次堆操作复杂度为 $O(\log n)$，所以时间复杂度是 $O(n \log n)$。

空间复杂度是 $O(n)$。

### 总结

这题是 Huffman 贪心模板：反复合并当前最小的两堆。Python 里记住 `heapq` 这组小根堆函数即可。
