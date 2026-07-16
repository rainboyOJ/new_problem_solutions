---
oj: "luogu"
problem_id: "P5283"
title: "[十二省联考 2019] 异或粽子"
description: "可持久化 01-Trie 求每个右端点的第 r 大子数组异或，用堆归并取全局前 k 大。"
difficulty: "省选/NOI-"
date: 2026-07-16 19:57
toc: true
tags: ["可持久化Trie", "异或", "堆", "前k大", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5283
---

[[TOC]]

### 题意

每个非空连续区间产生一个区间异或值，从所有不同区间中选择 `k` 个，使异或值之和最大。

### 思路

设前缀异或为 `prefix[i]`，区间 `[l,r]` 的值是 `prefix[r] ^ prefix[l-1]`。固定右端点 `r` 后，候选集合就是 `prefix[r]` 与 `prefix[0:r]` 中每个值的异或。

建立前缀异或的可持久化 01-Trie，`roots[r]` 恰好包含 `prefix[0]` 到 `prefix[r-1]`。沿位从高到低，根据子树计数即可求固定右端点的第 `rank` 大异或。

每个右端点形成一个递减候选序列。先把每列第 1 大放入最大堆；弹出一项后，只把同一列第 2、3……大依次补入。弹 `k` 次就是全局前 `k` 大的和。

### Python 知识

- `heapq` 是小根堆，存负值即可模拟最大堆。
- 堆元素 `(-value, end, rank)` 同时记录来源列与下一排名。
- 三个 `array("i")` 保存左右儿子和节点计数，避免上千万节点对象。
- `array("I")` 保存 32 位无符号前缀异或。

### 代码

@include-code(./main.py, python)

### 复杂度

Trie 建立 $O(32n)$，每次第 `rank` 大查询 $O(32)$，堆操作 $O(\log n)$；总时间 $O(32(n+k)+(n+k)\log n)$，空间 $O(32n+n)$。

### 总结

“每个右端点一列有序候选 + 堆归并”把无法枚举的 $O(n^2)$ 个区间压缩为只访问前 `k` 个需要的值。
