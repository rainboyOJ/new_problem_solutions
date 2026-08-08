---
oj: "luogu"
problem_id: "P4053"
title: "[JSOI2007] 建筑抢修"
description: "按截止时间扫描，最大堆维护已选工期；超时则用更短任务替换最长任务。"
difficulty: "普及+/提高"
date: 2026-07-16 21:00
toc: true
tags: ["贪心", "最大堆", "调度", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4053
---

[[TOC]]

### 题意

单机任务有工期和截止时间，求最多能按时完成多少个。

### 思路

按截止时间排序。当前任务能按时完成就选择；否则若它比已选任务中最长工期更短，用它替换最长任务。任务数不变但总耗时减小，为后续留下更多余量。

### Python 知识

- `sorted(..., key=lambda item: item[1])` 明确按截止时间排序。
- 负工期最大堆让 `-heap[0]` 是已选最长任务。
- `heapreplace` 一次替换堆顶，并返回被替换负值用于修正总时间。

### 代码

@include-code(./main.py, python)

### 复杂度

排序和堆操作总计 $O(n\log n)$，空间 $O(n)$。

### 总结

以截止时间推进时，固定已选数量下总工期越小越优，因此超时应淘汰最长任务。
