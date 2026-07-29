---
oj: "leetcodecn"
problem_id: "top-k-frequent-elements"
title: "前 K 个高频元素"
description: "统计频次后排序取前 k，或用大小为 k 的最小堆保留频次最高的 k 个。"
difficulty: "普及+/提高"
date: 2026-07-29 12:18
toc: true
tags: ["堆", "排序", "哈希表"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/top-k-frequent-elements/
---

[[TOC]]

### 题意
返回数组中频次前 `k` 高的元素。

### 思路
先用哈希表统计每个元素的频次，再按频次降序排序取前 `k` 个。C++ 直接排序；Python 用 `Counter.most_common(k)`。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n \log n)$（排序），可用堆优化到 $O(n \log k)$。
- 空间复杂度：$O(n)$，频次表。

### 总结
频次统计 + 排序取前 k 是本题最直接的解法。堆优化时维护大小为 k 的最小堆，按频次弹出不够格的元素。
