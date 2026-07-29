---
oj: "leetcodecn"
problem_id: "merge-k-sorted-lists"
title: "合并 K 个升序链表"
description: "小根堆维护每条链当前头节点，每次弹出后推进，O(N log K)。"
difficulty: "提高+/省选-"
date: 2026-07-28 22:05
toc: true
tags: ["链表", "堆", "分治", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/merge-k-sorted-lists/
---

[[TOC]]

### 题意

合并 k 个升序链表，返回一个升序链表。

### 思路

分治两两合并 O(N log K)。堆方法：把所有链表的头节点放入小根堆，每次弹出最小值节点加入结果，并将该节点的 next 入堆。每个节点入堆出堆各一次，O(N log K)。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(N log K)，N 为总节点数，K 为链表数。
- 空间复杂度：O(K)，堆的大小。

### 总结

"多路归并用小根堆维护 k 个候选"是处理多路有序数据合并的标准模型。
