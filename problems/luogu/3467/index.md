---
oj: "luogu"
problem_id: "P3467"
title: "[POI 2008] PLA-Postering"
description: "用递增高度栈合并可由同一张海报延续的高度层，每次出现新高度层时计数。"
difficulty: "普及/提高-"
date: 2026-07-16 18:25
toc: true
tags: ["单调栈", "贪心", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3467
---

[[TOC]]

### 题意

相邻建筑形成高度轮廓，求用不重叠矩形海报完整覆盖墙面的最少张数。

### 思路

维护严格递增高度栈。新高度更低时，弹出已经结束的高度层；若栈中已经存在同高度，它可以延续同一张海报，不新增；若新高度大于栈顶，就开始一个新的高度层并把答案加一。建筑宽度不影响层数。

### Python 知识

- `zip(data, data)` 把剩余整数按 `(宽度,高度)` 两两读取。
- 栈底放高度 0 哨兵，避免空栈分支。
- 只保存高度，宽度用 `_` 明确忽略。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n)$，空间复杂度 $O(n)$。

### 总结

每个新出现且当前栈中不存在的高度层恰好对应一张新海报。
