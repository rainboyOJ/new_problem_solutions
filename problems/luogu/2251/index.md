---
oj: "luogu"
problem_id: "P2251"
title: "质量检测"
description: "单调递增 deque 保存窗口内仍可能成为最小值的下标。"
difficulty: "普及/提高-"
date: 2026-07-16 21:00
toc: true
tags: ["单调队列", "滑动窗口", "deque", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2251
---

[[TOC]]

### 题意

输出每个固定宽度窗口的最小值。

### 思路

队列保存下标且对应值严格递增。加入新值时，队尾不小于它的元素以后不可能成为最小值，全部弹出；队首若离开窗口也弹出。形成完整窗口后，队首值就是答案。

### Python 知识

- `collections.deque` 支持两端 $O(1)$ 删除。
- 队列存下标而非值，才能判断元素是否过期。
- `enumerate(values)` 同步取得窗口右端和新值。

### 代码

@include-code(./main.py, python)

### 复杂度

每个下标进出队各一次，时间 $O(n)$，空间 $O(m)$。

### 总结

固定窗口最值的标准结构是单调队列，不需要堆的懒删除和对数因子。
