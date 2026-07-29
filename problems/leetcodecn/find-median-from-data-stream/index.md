---
oj: "leetcodecn"
problem_id: "find-median-from-data-stream"
title: "数据流的中位数"
description: "两个堆维护数据流：大顶堆存较小半，小顶堆存较大半，堆顶即为中位数候选。"
difficulty: "提高+/省选-"
date: 2026-07-29 12:20
toc: true
tags: ["堆", "优先队列", "数据结构"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/find-median-from-data-stream/
---

[[TOC]]

### 题意
设计数据结构，支持动态添加数字和查询中位数。

### 思路
用两个堆维护数据流：
- `lo`（大顶堆）：存较小的一半，堆顶是这半的最大值。
- `hi`（小顶堆）：存较大的一半，堆顶是这半的最小值。

插入时先放入 `lo`，再弹出 `lo` 堆顶放入 `hi`（保证 `hi` 中所有值 $\geqslant$ `lo` 中所有值）。若 `lo` 比 `hi` 少，则从 `hi` 弹回 `lo`（保证 `lo` 元素数 $\geqslant$ `hi`）。

两个不变式：`lo` 中所有值 $\leqslant$ `hi` 中所有值；`lo` 元素数比 `hi` 多 0 或 1。

查询中位数：`lo` 多时取 `lo` 堆顶，否则取两堆顶平均值。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：`addNum` $O(\log n)$，`findMedian` $O(1)$。
- 空间复杂度：$O(n)$。

### 总结
双堆中位数的关键是两个不变式：大小关系和元素数关系。插入时的"过一遍对方堆"保证大小关系，"多则弹回"保证元素数关系。Python 中 `lo` 用负数模拟大顶堆。
