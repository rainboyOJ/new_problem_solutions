---
oj: "luogu"
problem_id: "P2032"
title: "扫描"
description: "用单调递减队列保留窗口最大值候选，并以紧凑数组支持两百万规模输入。"
difficulty: "普及/提高-"
date: 2025-12-26 19:31
toc: true
tags: ["单调队列", "滑动窗口", "python"]
categories: []
pre: []
common:
  - oj: "luogu"
    problem_id: "P1714"
    reason: "同为单调队列维护滑动窗口的应用。"
recommend: []
source: https://www.luogu.com.cn/problem/P2032
---

[[TOC]]

### 题意

输出序列中每个长度为 $k$ 的连续窗口最大值。

### 思路

队列保存值严格递减的候选。新数加入时，队尾所有不大于它的旧数更早过期且更小，可以永久删除；队头下标离开窗口时删除。窗口形成后队头就是最大值。

### Python 知识

- $n$ 可达两百万，使用两个 `array("i")` 模拟紧凑双端队列，避免大量 Python 元组。
- `os.read` 分块解析整数，避免 `read().split()` 的峰值内存。
- 答案按 8192 行分块写出，避免保存全部输出字符串。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n)$，空间复杂度 $O(n)$。

### 总结

滑动窗口最值只需保留尚未过期且没有被更优新元素淘汰的候选。
