---
oj: "luogu"
problem_id: "P3509"
title: "[POI 2010] ZAB-Frog"
description: "双指针求每块石头的一跳终点，再对整个映射做二进制快速幂。"
difficulty: "省选/NOI-"
date: 2026-07-16 18:28
toc: true
tags: ["双指针", "倍增", "函数复合", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3509
---

[[TOC]]

### 题意

石头坐标严格递增。青蛙每次跳到距离排名为 `k` 的石头，距离相同则选坐标较小者。对每个起点求跳 `m` 次后的终点。

### 思路

对当前石头 `i`，包含它在内的 `k + 1` 个最近点在有序坐标中一定构成连续窗口 `[left, right]`。窗口右侧下一个点比左端点更近时，就整体右移。指针只增不减，所以所有一跳终点可在线性时间求出。

窗口中离 `i` 更远的端点就是目标；两端距离相等时选择左端，恰好满足题目的平局规则。

得到一跳映射 `transition` 后，要计算它复合 `m` 次。像快速幂一样：

- 当前二进制位为 `1` 时，把答案映射复合一次；
- 每轮令 `transition = transition o transition`。

### Python 知识

- `array("q")` 保存最高可达 $10^{18}$ 的坐标，`array("i")` 保存下标，显著降低百万规模数据的内存。
- 自定义 `read_ints()` 用 `os.read` 分块解析整数，避免 `read().split()` 为一百万个 token 创建大量 `bytes` 对象。
- `map(transition.__getitem__, answer)` 表示把映射同时作用到所有当前答案上。
- `while moves:` 与位运算实现“映射的快速幂”。

### 代码

@include-code(./main.py, python)

### 复杂度

双指针 $O(n)$，映射快速幂 $O(n\log m)$；空间 $O(n)$。

### 总结

倍增不一定要保存二维跳表。需要同时求所有起点且内存紧张时，可以像数值快速幂一样不断平方整个映射。
