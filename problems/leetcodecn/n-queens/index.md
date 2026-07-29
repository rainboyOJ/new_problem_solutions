---
oj: "leetcodecn"
problem_id: "n-queens"
title: "N 皇后"
description: "逐行放置皇后，用三个数组（列、主对角线、副对角线）检测冲突，回溯搜索所有合法方案。"
difficulty: "普及+/提高"
date: 2026-07-29 11:40
toc: true
tags: ["回溯", "枚举", "递归"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/n-queens/
---

[[TOC]]

### 题意

在 $n \times n$ 棋盘上放置 $n$ 个皇后，使任意两个皇后不在同一行、同一列或同一斜线上。返回所有合法方案的棋盘表示。

### 思路

最直接的思路是枚举每行皇后放在哪一列，全部决定后再检查冲突：

@include-code(./brute.cpp, cpp)

brute.cpp 先生成完整排列再检查冲突，复杂度 $O(n^n)$，对 $n \geqslant 8$ 会超时。

优化的关键是：逐行放置时用三个冲突集合实时剪枝。

- `col[c]`：第 `c` 列是否已有皇后。
- `diag1[r+c]`：主对角线（左上到右下）是否已有皇后。同一主对角线上的格子满足 `r+c` 相等。
- `diag2[r-c+n-1]`：副对角线（右上到左下）是否已有皇后。同一副对角线上的格子满足 `r-c` 相等（偏移 `n-1` 避免负下标）。

每行只放一个皇后，所以行冲突天然不存在。三个数组实时标记当前占据的列和对角线，放置前检查、放置后标记、递归后恢复，保证每一步只扩展合法分支。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n!)$，第一行 n 个选择，第二行最多 n-1 个，逐行递减。
- 空间复杂度：$O(n)$，三个冲突数组加递归栈。

### 总结

N 皇后是回溯剪枝的经典模型。关键是用 `col`、`diag1`、`diag2` 三个数组将冲突检测从 $O(n)$ 降到 $O(1)$。对角线的下标定义：主对角线 `r+c`，副对角线 `r-c+n-1`，使得同一对角线上所有格子的下标相等。
