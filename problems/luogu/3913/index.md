---
oj: "luogu"
problem_id: "P3913"
title: "车的攻击"
description: "用集合统计被占用的不同行列，再用容斥计算这些整行整列覆盖的格子数。"
difficulty: "入门"
date: 2026-07-16 19:20
toc: true
tags: ["集合", "容斥原理", "计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3913
---

[[TOC]]

### 题意

在 `n*n` 棋盘上放若干车，统计至少被一辆车所在行或所在列覆盖的格子数。

### 思路

只需知道有多少个不同的被攻击行 `R` 和列 `C`。所有行覆盖 `R*n` 个格子，所有列覆盖 `C*n` 个格子，行列交叉的 `R*C` 个格子被重复计算一次，因此答案是：

$$Rn+Cn-RC$$

车的位置可能重复行或重复列，分别用集合去重。

### Python 知识

- `set.add` 自动忽略重复行列编号。
- `len(rows)`、`len(columns)` 就是容斥公式所需的集合大小。
- 逐行读取百万个车，避免一次性 token 列表带来的峰值内存。
- Python 大整数可直接容纳 `n<=1e9` 的棋盘计数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：集合成员去重。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：大规模逐行输入。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sys.stdin 快读：

@include-code(./main-pythonic.py, python)

### 复杂度

期望时间复杂度 $O(k)$，空间复杂度 $O(k)$。

### 总结

棋盘虽然巨大，但覆盖只由行集合和列集合决定；集合去重加两集合容斥即可。
