---
oj: "luogu"
problem_id: "P4513"
title: "小白逛公园"
description: "线段树维护区间和、最大前缀、最大后缀和最大子段和，支持单点修改。"
difficulty: "普及+/提高"
date: 2026-07-16 23:59
toc: true
tags: ["线段树", "最大子段和", "点修改", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4513
---

[[TOC]]

### 题意

区间查询最大连续子段和，另有单点赋值操作；查询端点可能反向给出。

### 思路

节点保存 `sum`、最大前缀 `prefix`、最大后缀 `suffix` 和最大子段 `best`。合并左右节点时，跨中点的候选是 `left.suffix + right.prefix`，其余三项分别取左右最大值。查询部分区间时返回一个五元组，最后按相同公式合并。

### Python 知识

- `merge` 返回元组，适合把一个区间的四个统计量和长度作为整体传递。
- `array("q")` 让四棵大规模 64 位统计数组保持紧凑。
- 用 `None` 表示还没有取到左子区间，避免为查询补造无效的负无穷节点。
- `max` 的多个参数直接表达三种最大子段来源。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

建树 `O(n)`，每次修改或查询 `O(log n)`，空间 `O(n)`。

### 总结

最大子段和不是只存一个最大值；前缀和后缀正是跨越中点所需的边界信息。
