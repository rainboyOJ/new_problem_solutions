---
oj: "luogu"
problem_id: "P1763"
title: "埃及分数"
description: "迭代加深枚举单位分数个数，用剩余项上界和最优末分母剪枝。"
difficulty: "提高+/省选-"
date: 2026-07-16 20:10
toc: true
tags: ["迭代加深", "DFS", "分数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1763
---

[[TOC]]

### 题意

把真分数表示成分母严格递增的单位分数和。项数越少越优；项数相同时，最大分母越小越优。

### 思路

按项数从 1 开始迭代加深，第一个有解的层数保证项数最少。剩余分数为 `a/b` 时，下一个分母至少为 `ceil(b/a)`。

若还剩 `slots` 项且下一分母为 `x`，所有后续单位分数都不超过 `1/x`，必须满足 `slots/x >= a/b`，由此得到枚举上界 `slots*b//a`。最后一项必须恰好等于剩余分数，可以直接判整除。

同一深度记录最大分母最小的方案。

### Python 知识

- `math.gcd` 每步约分，避免分子分母无谓膨胀。
- 海象运算符在循环条件中同时取得当前深度搜索结果。
- `path.append/pop` 原地维护当前分母序列。

### 代码

@include-code(./main.py, python)

### 复杂度

搜索复杂度取决于最优项数与分母范围，最坏指数级；递归空间等于答案项数。

### 总结

题目按“项数优先”排序答案时，IDDFS 自然匹配第一关键字，再在同层比较第二关键字。
