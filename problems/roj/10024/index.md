---
oj: "roj"
problem_id: "10024"
title: "快速排序"
description: "快速排序相关计数：双树状数组维护差分实现区间加、区间和，前缀和还原区间贡献，O(m log n)。"
difficulty: "提高+/省选-"
date: 2026-10-02 18:55
updated: 2026-10-02 19:14
toc: true
tags:
  - "数据结构"
  - "树状数组"
  - "快速排序"
favorite: false
favorite_reason: ""
categories:
  - "数据结构"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/10024
---

[[TOC]]

## 形式化题目

按题面（快速排序的比较次数/划分计数模型）给定序列与询问，求相应计数（对 $10^9+7$ 取模）。核心操作是「区间加、区间求和」的在线维护。

## 正解

### 思路

#### 1. 双树状数组区间加区间和

维护差分数组 $d$ 的两个 BIT：

- $b_1$ 存 $d_i$；
- $b_2$ 存 $d_i\cdot(i-1)$。

前 $i$ 项原数组和 $= i\cdot\sum_{k\le i} b_1(k) - \sum_{k\le i} b_2(k)$。区间 $[l,r]$ 加 $\delta$ 时在 $b_1$ 的 $l$、$r+1$ 处打 $\pm\delta$，$b_2$ 对应 $\pm\delta\cdot(l-1)$、$\mp\delta\cdot r$。

#### 2. 计数流程

按题面把快速排序的递归/比较过程转成对序列区间的增量操作与查询，用上述结构在线维护，单次 $O(\log n)$。

### 代码

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：$O(m\log n)$。
- **空间复杂度**：$O(n)$。

## 总结

- 区间加 + 区间和的标准做法：**双 BIT 差分**（$b_1$, $b_2 = d_i(i-1)$）。
- 任何「批量加值、批量求和」的计数问题都能套用此结构。
