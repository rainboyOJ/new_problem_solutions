---
oj: "luogu"
problem_id: "P2161"
title: "[SHOI2009] 会场预约"
description: "Fenwick 维护当前不相交线段的起点，并按秩寻找可能相交的前驱和后继。"
difficulty: "提高+/省选-"
date: 2026-07-16 21:00
toc: true
tags: ["树状数组", "有序集合", "线段", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2161
---

[[TOC]]

### 题意

插入新区间时删除所有与它相交的旧区间并输出删除数；另支持查询当前区间数。

### 思路

集合中的旧区间始终两两不交，因此按起点有序。日期上界只有 `10^5`，Fenwick 在每个起点保存是否存在区间，`end_at[start]` 保存终点。

先找起点不超过新左端的最后一条，检查它是否延伸到左端；再反复找第一个起点不小于左端的区间，直到起点超过新右端。每条被删线段都做一次 Fenwick 删除，最后加入新区间。

### Python 知识

- Fenwick 的 `kth(rank)` 用二进制提升实现动态集合按秩查找。
- `bytes` 操作码直接与 `b"B"` 比较。
- 所有历史删除总数不超过插入总数，循环总成本仍是线性的删除次数乘对数。

### 代码

@include-code(./main.py, python)

### 复杂度

每次查找/修改 $O(\log C)$，所有删除合计 $O(n)$，总时间 $O(n\log C)$，空间 $O(C)$，其中 $C=10^5$。

### 总结

值域较小时，Fenwick 加按秩查询可以替代平衡树维护动态有序起点集合。
