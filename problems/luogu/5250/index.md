---
oj: "luogu"
problem_id: "P5250"
title: "【深基17.例5】木材仓库"
description: "离线压缩所有长度，用树状数组维护库存并按排名寻找最近的前驱和后继。"
difficulty: "普及+/提高"
date: 2026-07-16 18:26
toc: true
tags: ["树状数组", "离散化", "前驱后继", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5250
---

[[TOC]]

### 题意

维护一个长度互不相同的木材集合。支持插入；出货时删除等于需求长度的木材，否则删除距离需求最近的木材，距离相同选较短者。还要处理重复插入和空仓库。

### 思路

Python 标准库没有直接提供有序集合。普通有序列表配合 `bisect` 虽能找到位置，但中间插入、删除需要移动大量元素，最坏会达到 $O(q^2)$。

所有操作在开始时已经给出，可以先离线读完，把出现过的长度排序去重并映射到 `1..k`。树状数组的第 `i` 位表示该长度当前是否在仓库：

- 插入、删除是单点加 `1` 或 `-1`；
- 前缀和表示某个长度之前有多少根现存木材；
- `kth(rank)` 找库存中第 `rank` 小的长度。

出货长度 `x` 不存在时，设严格小于 `x` 的库存数量为 `left_count`。第 `left_count` 小的是前驱，第 `left_count+1` 小的是后继。比较两边距离，使用 `x-left <= right-x` 保证距离相同时选较短的前驱。

### Python 知识

- 集合推导式 `{length for _, length in operations}` 完成长度去重。
- `enumerate(lengths,1)` 同时得到长度及其从 `1` 开始的树状数组下标。
- `set` 负责期望 $O(1)$ 存在性判断，树状数组负责顺序和排名；两个容器各做自己擅长的事。
- `None` 表示某一侧不存在候选，比设置超大哨兵更直观。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：排序、离散化与有序查询。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：集合的成员判断。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)


### 复杂度

设操作数为 `q`。离散化需要 $O(q\log q)$，每次操作需要 $O(\log q)$，总时间复杂度 $O(q\log q)$，空间复杂度 $O(q)$。

### 总结

需要动态前驱、后继时，不能只看到 `bisect` 查询快，还要计算列表修改成本。离线坐标压缩把大整数长度变成排名，再用树状数组维护哪些排名仍存在。
