---
oj: "luogu"
problem_id: "P1908"
title: "逆序对"
description: "离散化数值，用树状数组统计每个数左边有多少个更大的数。"
difficulty: "普及+/提高"
date: 2026-07-16 18:28
toc: true
tags: ["树状数组", "离散化", "逆序对", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1908
---

[[TOC]]

### 题意

统计满足 $i<j$ 且 $a_i>a_j$ 的下标对数量。

### 思路

从左到右扫描。处理 `value` 时，树状数组记录了此前每个排名出现了几次：

- `prefix` 是已经出现且小于等于 `value` 的数目；
- `seen - prefix` 就是左边严格大于 `value` 的数目，也是新产生的逆序对数。

原值可能很大，还有重复值，所以先将 `sorted(set(values))` 映射到从 `1` 开始的连续排名。相等元素使用同一排名，并被 `prefix` 包含，因此不会误算成逆序对。

### Python 知识

- `sorted(set(values))` 同时完成去重和排序。
- 字典推导式把原值映射为树状数组下标。
- `iter(map(int, sys.stdin.buffer.read().split()))` 适合一次读入大量整数。
- `i & -i` 是树状数组的 `lowbit`；查询时减去它，修改时加上它。

### 代码

@include-code(./main.py, python)

原有 C++ 归并排序版本仍保留在目录中：

@include-code(./main.cpp, cpp)

### 复杂度

离散化和每次树状数组操作均为 $O(\log n)$，总时间 $O(n\log n)$，空间 $O(n)$。

### 总结

“扫描到当前位置时，统计左边比它大的数”是逆序对的另一种标准视角。Python 的集合、排序、字典推导式让离散化只需一行核心代码。
