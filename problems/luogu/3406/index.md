---
oj: "luogu"
problem_id: "P3406"
title: "海底高铁"
description: "用路线端点差分统计每段铁路经过次数，再逐段比较纸票与购卡后的独立费用。"
difficulty: "普及/提高-"
date: 2026-07-16 17:48
toc: true
tags: ["差分", "贪心", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3406
---

[[TOC]]

### 题意

按给定城市顺序旅行。每段相邻铁路可每次买纸票，也可支付固定费用购卡后享受单次低价，求最小总费用。

### 思路

一次从 `start` 到 `end` 的移动，会经过编号 `[min(start,end), max(start,end))` 的铁路段。用差分给这段经过次数整体加一，前缀还原后即可得到每段的总使用次数 `count`。

各铁路段互不影响，逐段选择 `min(count*A, count*B+C)` 并求和。

### Python 知识

- `pairwise(route)` 直接枚举相邻访问城市。
- `sorted((start, end))` 一行处理双向移动。
- `accumulate(difference)` 还原每段经过次数，参见 `/home/rainboy/mycode/hugo-blog/content/program_language/python/itertools_recipes.md`。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(N+M)$，空间复杂度 $O(N+M)$。

### 总结

先把整条路线压缩成每段使用次数，购卡决策就变成互相独立的局部取最小值。
