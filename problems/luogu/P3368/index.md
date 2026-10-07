---
oj: "luogu"
problem_id: "P3368"
title: "【模板】树状数组 2"
description: "在差分数组上用 Fenwick 做两个端点修改，前缀和恢复单点值。"
difficulty: "普及/提高-"
date: 2026-07-16 21:00
updated: 2026-10-07 12:15
toc: true
tags: ["树状数组", "差分", "区间修改", "python"]
categories: []
pre:
  - oj: "luogu"
    problem_id: "P2367"
    reason: "B 的区间加单点查把 A 教的差分两端点修改逐字搬进树状数组（d[l]+=x、d[r+1]-=x，位置值是差分前缀和），再叠加 Fenwick 维护与越界 r+1 判断"
  - oj: "roj"
    problem_id: "1547"
    reason: "B 的 add/prefix 与 A 教的 Fenwick 单点修改上跳、前缀下跳模板逐字相同（代码里都是 index += index & -index 与 index -= index & -index），B 只是把维护对象换成差分数组，再叠加 A 未教的「区间加=两端点差分修改」这一步。"
  - oj: "roj"
    problem_id: "1535"
    reason: "B 复用 A 教的沿 lowbit 向上 add、向下 prefix 的 Fenwick 模板，只是把维护对象从原数组换成差分数组，从而把单点加/区间查对偶成区间加/单点查。"
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3368
---

[[TOC]]

### 题意

支持区间整体加值，以及查询某个位置当前值。

### 思路

维护差分 `d[i]=a[i]-a[i-1]`。区间 `[l,r]` 加 `x` 只需 `d[l]+=x`、`d[r+1]-=x`；原数组位置 `p` 是差分前缀和。

Fenwick 正好支持两个差分点修改与前缀查询。初始数组读入时相邻相减后加入树。

### Python 知识

- 流式读入时只保存 `previous` 就能构造差分，不必保留原数组。
- `if right < n` 避免修改越界的 `r+1`。
- 与 P3374 共用相同 `add/prefix` 模板，含义由维护对象决定。

### 代码

@include-code(./main.py, python)

### 复杂度

每次操作 $O(\log n)$，空间 $O(n)$。

### 总结

区间加、单点查应先想到差分；Fenwick 维护的不是原数组，而是差分数组。
