---
oj: "luogu"
problem_id: "P1884"
title: "[USACO12FEB] Overplanting S"
description: "沿 x 轴扫描矩形左右边事件，每个竖条内合并当前活跃的 y 区间以计算覆盖面积。"
difficulty: "普及+/提高"
date: 2026-07-16 17:48
toc: true
tags: ["扫描线", "区间合并", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1884
---

[[TOC]]

### 题意

求至多 $1000$ 个轴对齐矩形的覆盖并集面积，重复覆盖只计算一次。

### 思路

每个矩形在左边界加入一个 $y$ 区间，在右边界删除它。相邻两个事件横坐标之间，活跃矩形集合不变，因此面积增量是：

$$
(x-\text{previous\_x})\times \text{活跃 y 区间并集长度}。
$$

同一横坐标的事件必须成组处理。`Counter` 保存区间的出现次数，也能正确处理多个矩形具有相同纵向区间的情况。

### Python 知识

- `Counter[(low, high)] += change` 把元组直接作为键，参见 `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`。
- 对 `active.items()` 排序后复用一维区间合并逻辑。
- 事件使用元组排序，自然按横坐标聚集。

### 代码

@include-code(./main.py, python)

### 复杂度

本题规模下直接重算活跃区间并集，时间复杂度 $O(n^2\log n)$，空间复杂度 $O(n)$。

### 总结

扫描线把二维面积拆成若干“宽度乘覆盖高度”的竖条。
