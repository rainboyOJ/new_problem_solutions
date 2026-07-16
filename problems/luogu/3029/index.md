---
oj: "luogu"
problem_id: "P3029"
title: "[USACO11NOV] Cow Lineup S"
description: "按坐标排序奶牛，用 Counter 和双指针维护包含全部品种的最短坐标窗口。"
difficulty: "普及/提高-"
date: 2026-07-16 17:48
toc: true
tags: ["双指针", "滑动窗口", "计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3029
---

[[TOC]]

### 题意

在数轴上选择一个最短区间，使其中至少包含全体奶牛中每一种品种。

### 思路

先按坐标排序。右指针逐个加入奶牛；窗口已经包含全部品种时，不断移动左指针并更新长度，直到刚好缺少一种品种。

### Python 知识

- `Counter` 保存窗口内各品种次数，删除计数归零的键后，`len(counts)` 就是当前品种数。
- 集合推导式 `{breed for _, breed in cows}` 统计全局不同品种。
- 元组排序同时保留坐标和品种信息，参见 `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

### 总结

“最短区间覆盖全部类别”是排序后滑动窗口的典型模型。
