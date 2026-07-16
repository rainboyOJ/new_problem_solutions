---
oj: "luogu"
problem_id: "P3374"
title: "【模板】树状数组 1"
description: "Fenwick 维护单点增量与前缀和，用两个前缀和相减回答区间和。"
difficulty: "普及/提高-"
date: 2026-07-16 21:00
toc: true
tags: ["树状数组", "前缀和", "模板题", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3374
---

[[TOC]]

### 题意

支持某一项加值，以及查询任意闭区间元素和。

### 思路

Fenwick 节点保存一段由 `lowbit` 决定的后缀和。修改下标时不断加 `lowbit`，查询前缀时不断减 `lowbit`；区间 `[l,r]` 等于 `prefix(r)-prefix(l-1)`。

### Python 知识

- 自定义 `os.read` 分块整数生成器避免 150 万级 token 的 `split` 内存峰值。
- `array("q")` 用 64 位整数紧凑保存树。
- `i & -i` 取得最低位 1。

### 代码

@include-code(./main.py, python)

### 复杂度

初始化与每次操作 $O(\log n)$，空间 $O(n)$。

### 总结

Fenwick 是动态前缀和的最短模板，区间查询仍通过前缀差完成。
