---
oj: "luogu"
problem_id: "P2827"
title: "[NOIP 2016 提高组] 蚯蚓"
description: "用全局增量抵消统一加 q，并以三个单调队列线性取当前最长蚯蚓。"
difficulty: "提高+/省选-"
date: 2026-07-16 21:00
toc: true
tags: ["单调队列", "偏移量", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2827
---

[[TOC]]

### 题意

反复取最长蚯蚓切成两段，其余长度统一加 `q`，按指定间隔输出切割值和最终排名。

### 思路

把统一增长记为全局 `offset`，队列中只存“实际长度减 offset”。初始降序序列是一条队列；每次切出的两类长度各自也按生成顺序单调不增，形成另外两条队列。当前最大值只需比较三个队首。

第 `i` 秒新段不参与本秒的 `q`，存入时减去 `i*q`。完成后继续三路归并即可得到最终降序序列。

### Python 知识

- 两个 `array("q")` 紧凑容纳最多七百万个生成长度。
- 头下标代替 `pop(0)`，避免移动数组。
- `max(range(3), key=candidates.__getitem__)` 找三队列最大队首。

### 代码

@include-code(./main.py, python)

### 复杂度

排序 $O(n\log n)$，之后时间 $O(n+m)$，空间 $O(n+m)$。

### 总结

“除新元素外全部统一增加”通常可以用全局懒偏移消去；再识别生成序列单调性，就无需大堆。
