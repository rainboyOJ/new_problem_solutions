---
oj: "luogu"
problem_id: "P4799"
title: "[CEOI 2015] 世界冰球锦标赛 (Day2)"
description: "折半生成两组子集和，排序一边并用 bisect_right 统计预算内组合。"
difficulty: "提高+/省选-"
date: 2026-07-16 20:10
toc: true
tags: ["Meet-in-the-Middle", "子集和", "二分", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4799
---

[[TOC]]

### 题意

至多 40 场比赛，每场可选或不选，统计总票价不超过预算的方案数，包括空集。

### 思路

直接枚举 $2^{40}$ 不可行。左右各约 20 场，分别生成所有不超预算的子集和。对每个左和 `x`，右边可以选择所有不超过 `budget-x` 的子集和。

把右和排序后，`bisect_right(right, budget-x)` 的返回下标正好是合法右方案数，累加即可。相同价格的不同比赛产生不同枚举分支，列表中的重复和不能去重。

### Python 知识

- `sums += [total + value for total in sums ...]` 由旧子集和批量生成“选择当前项”的新和。
- `bisect_right` 直接统计小于等于上界的元素个数。
- `sum(generator)` 流式累加全部左半查询结果。

### 代码

@include-code(./main.py, python)

### 复杂度

时间 $O(2^{n/2}\log 2^{n/2})$，空间 $O(2^{n/2})$。

### 总结

40 是子集枚举的典型折半信号；一边排序后，二边组合计数就变成普通上界查询。
