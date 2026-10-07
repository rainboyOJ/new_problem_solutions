---
oj: "luogu"
problem_id: "P3378"
title: "【模板】堆"
description: "用 heapq 直接维护可重复整数小根堆，并用 bytearray 批量输出。"
difficulty: "普及"
date: 2026-07-16 21:00
updated: 2026-10-07 10:17
toc: true
tags: ["二叉堆", "heapq", "模板题", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3378
---

[[TOC]]

### 题意

维护一个可重小根堆，支持插入、查询最小值和删除一个最小值。

### 思路

Python 标准库 `heapq` 在普通列表上实现小根堆：`heappush` 插入，`heap[0]` 查看堆顶，`heappop` 删除堆顶，正好对应三种操作。

### Python 知识

- `heapq` 原生是小根堆，重复值无需特殊处理。
- 百万次操作逐行读取，避免一次 `split` 的内存峰值。
- 查询结果追加到 `bytearray`，最后一次写出。

### 代码

C++ 用 `priority_queue<ll, vector<ll>, greater<ll> >` 就是标准库提供的小根堆：第三个模板参数 `greater<ll>` 把“数值小”当作“优先级高”，于是 `push`、`top`、`pop` 正好对应插入、查最小值和删除最小值三种操作，和上面 Python 的 `heapq` 一一对应，不必手写上浮下沉。堆内允许重复元素，`top()` 取到的始终是当前最小值，删除时也只弹出一个。

对应的 cppbook 章节：[priority_queue：优先处理最重要的元素](https://cppbook.roj.ac.cn/stl/container-adapters/priority-queue/)

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### 复杂度

插入、删除 $O(\log n)$，查看最小值 $O(1)$，空间 $O(n)$。

### 总结

Python OJ 的堆模板就是 `heapq` 三个基本接口，不必手写上浮下沉。
