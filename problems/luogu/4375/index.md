---
oj: "luogu"
problem_id: "P4375"
title: "[USACO18OPEN] Out of Sorts G"
description: "稳定排序后统计每条位置边界上向右跨越的元素数，其最大值就是双向冒泡所需轮数。"
difficulty: "提高+/省选-"
date: 2026-07-16 17:48
toc: true
tags: ["排序", "差分", "思维", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4375
---

[[TOC]]

### 题意

题面算法每轮先从左向右冒泡，再从右向左冒泡，最后检查是否有逆序对。求进入循环并输出 `moo` 的次数。

### 思路

把元素写成 `(value, original_position)` 后稳定排序，得到每个元素的目标位置。若元素从 `original_position` 移到更右的 `sorted_position`，它会跨过其间每一条边界。

一次双向扫描至多让每条边界上的一个“待跨越元素”完成交换，因此答案是所有边界跨越数的最大值。对区间 `[original+1, sorted_position]` 做差分加一，再取前缀最大值即可。已经有序时循环仍执行一次，所以答案至少为 $1$。

### Python 知识

- `sorted(range(n), key=lambda i: (values[i], i))` 明确实现按值、原下标的稳定次序。
- `int.bit_count` 等技巧不需要出现在正解中；位置跨越用普通差分更直接。
- `max(accumulate(difference))` 把差分还原和求最大值连在一起。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

### 总结

无需模拟冒泡排序；排序后的位移把“多少轮”转成“最多有多少元素跨过同一边界”。
