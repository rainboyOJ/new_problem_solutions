---
oj: "luogu"
problem_id: "P1168"
title: "中位数"
description: "最大堆和最小堆维护前缀的较小一半与较大一半，奇数长度输出最大堆顶。"
difficulty: "普及/提高-"
date: 2026-07-16 21:00
toc: true
tags: ["双堆", "中位数", "heapq", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1168
---

[[TOC]]

### 题意

依次读入序列，对每个奇数长度前缀输出中位数。

### 思路

`lower` 负数最大堆保存较小一半，`upper` 小根堆保存较大一半。每次插入后调整到 `len(lower)` 等于或比 `upper` 多 1，奇数长度时中位数就是 `-lower[0]`。

### Python 知识

- `-value` 是 Python 3.14 以前通用的最大堆写法。
- `enumerate` 的偶数下标对应已读奇数个元素。
- 两个 `heappop/heappush` 完成跨堆再平衡。

### 代码

@include-code(./main.py, python)

### 复杂度

每项 $O(\log n)$，空间 $O(n)$。

### 总结

动态中位数的本质是维持有序序列在中点处的两半，而不是每次重新排序。
