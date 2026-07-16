---
oj: "luogu"
problem_id: "P2853"
title: "[USACO06DEC] Cow Picnic S"
description: "从每头牛的起点分别搜索，用计数数组统计被全部搜索到的牧场。"
difficulty: "普及-"
date: 2026-07-16 18:42
toc: true
tags: ["有向图", "DFS", "可达性", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2853
---

[[TOC]]

### 题意

有 `k` 头牛、`n` 个牧场和 `m` 条单向路。每头牛各自在一个牧场，求有多少个牧场能被所有牛到达。

### 思路

数据范围允许从每头牛的起点各做一次图搜索。

第 `i` 次搜索中，每到达牧场 `v`，令 `reachable_count[v]+=1`。全部搜索结束后，计数等于 `k` 的牧场就是所有牛可达集合的交集。

每次搜索必须有独立的 `visited`，保证同一头牛不会因为不同路径重复给一个牧场计数。

### Python 知识

- `bytearray(n+1)` 是紧凑的 0/1 访问标记数组。
- 普通列表的 `append/pop` 可直接作为后进先出栈。
- `reachable_count.count(k)` 直接统计值恰好为牛数量的牧场个数。
- 批量整数输入后用切片取得所有起点，再用指针读取边。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：图搜索状态与访问标记。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：容器选择和计数。

### 代码

@include-code(./main.py, python)

### 复杂度

每头牛搜索一次，时间复杂度 $O(k(n+m))$；图、访问数组和计数数组空间复杂度 $O(n+m)$。

### 总结

“所有起点都能到达”的交集，可以转成“每个起点各投一票”。最终票数等于起点数的节点就是答案。
