---
oj: "roj"
problem_id: "3128"
title: "营业额统计"
description: "每天营业额的最小波动值（与之前某天差的绝对值最小）：数组式 Treap 逐日插入 + 最近值查询，期望 O(n log n)，避免递归爆栈。"
difficulty: "省选/NOI-"
date: 2026-10-01 18:40
updated: 2026-10-10 11:30
toc: true
tags:
  - "平衡树"
  - "Treap"
  - "离线查询"
favorite: false
favorite_reason: ""
categories:
  - "数据结构"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3128
---

[[TOC]]

## 形式化题目

给定 $n$ 天营业额 $a_1..a_n$。第 $i$ 天的波动值定义为 $\min_{j<i} |a_i - a_j|$（第 1 天波动值为 $a_1$ 本身，按题面约定）。求每天波动值之和。

## 正解

### 思路

#### 1. 在线动态「最近值」

逐日处理：每天需要在**已出现的营业额集合**里找与 $a_i$ 最接近的值，然后把 $a_i$ 插入集合。这是平衡树的模板操作：

- **插入**：把 $a_i$ 放入 BST；
- **最近值查询**：从根向下走，沿途维护「当前最优候选」，到空节点时返回最小距离。候选只可能是下降路径上每次「转向」时的分界值（前驱/后继）。

#### 2. 数组式 Treap

用平铺数组 `left/right/key/prio` 实现 Treap（随机优先级小根堆维护平衡）：

- **迭代插入 + 显式 path 栈**上浮旋转，避免递归（Python 递归深度与常数都不友好）；
- 旋转后按「祖父—父—子」的指针重接，逻辑清晰不易错。

期望树高 $O(\log n)$，总复杂度 $O(n\log n)$。Python 通过数组 + 迭代避免了链式对象与递归的双重常数，足以通过本题时限。

### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：期望 $O(n\log n)$。
- **空间复杂度**：$O(n)$。

## 总结

- 「与历史某值差最小」= 平衡树维护动态集合 + 前驱/后继查询。
- Python 写平衡树优先选**数组式 + 迭代**：省去对象开销与递归风险，常数显著更小。
- Treap 随机优先级保证期望平衡，代码量比 Splay/AVL 小，是竞赛中的实用选择。
