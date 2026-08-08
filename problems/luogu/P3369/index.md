---
oj: "luogu"
problem_id: "P3369"
title: "【模板】普通平衡树"
description: "离线收集所有数值并坐标压缩，用 Fenwick 维护多重集合、排名、kth、前驱和后继。"
difficulty: "提高+/省选-"
date: 2026-07-16 19:57
toc: true
tags: ["树状数组", "坐标压缩", "有序多重集", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3369
---

[[TOC]]

### 题意

动态维护可重集合，支持插入、删除、排名、第 `k` 小、严格前驱与严格后继。

### 思路

题目虽然叫平衡树，但全部操作已经在输入中，可以先离线收集所有作为“数值”的 `x` 并坐标压缩。树状数组在压缩坐标上维护每个值的出现次数。

- 排名：`小于 x 的数量 + 1`；
- 第 `k` 小：在 Fenwick 树上二进制提升，找最小前缀和达到 `k` 的坐标；
- 前驱：小于 `x` 的数量所对应的第 `count` 小；
- 后继：小于等于 `x` 的数量再加一所对应的元素。

重复值只改变同一坐标的计数，语义与可重集合一致。

### Python 知识

- `sorted({value for ...})` 一行完成离线去重排序。
- `bisect_left` 统计严格小于，`bisect_right` 统计小于等于。
- Fenwick 的 `kth` 使用 `bit_length()` 取得最高二进制步长。
- 操作保存成元组列表，第二遍执行时无需重新解析。

### 代码

@include-code(./main.py, python)

### 复杂度

设操作数为 $n$，预排序 $O(n\log n)$，每次操作 $O(\log n)$，空间 $O(n)$。

### 总结

OJ 输入允许离线时，不必强行在 Python 手写旋转平衡树；坐标压缩 + Fenwick 同样完整实现顺序统计接口。
