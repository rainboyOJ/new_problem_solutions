---
oj: "luogu"
problem_id: "P6824"
title: "「EZEC-4」可乐"
description: "在二进制 Trie 上按 k 的当前位分类，递推选择聪明值 x 的每一位。"
difficulty: "普及+/提高"
date: 2026-07-16 19:57
toc: true
tags: ["01-Trie", "数位DP", "异或", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P6824
---

[[TOC]]

### 题意

任选非负整数 `x`，最大化满足 `(a[i] ^ x) <= k` 的元素数量。

### 思路

把所有 `a[i]` 放进 01-Trie，并从最高位向低位决定 `x`。

若 `k` 当前位为 0，合法异或值当前位只能为 0，因此所有继续比较的数必须来自 `a` 的同一个位分支；`x` 可选 0 或 1，取两个子树递归结果的最大值。

若 `k` 当前位为 1：

- 异或位取 0 的整棵子树已经严格小于 `k`，其中所有数都合法；
- 异或位取 1 的另一棵子树还要继续比较低位。

枚举 `x` 当前位的两种选择，递推式就是“一个子树全收 + 另一个子树继续”。

### Python 知识

- `max(limit, max(values)).bit_length() - 1` 自动确定最高有效位。
- Trie 使用 1 号根，0 号专作空儿子，保证 `count[0] == 0`。
- 递归深度只有约 20，不会触及 Python 递归限制。
- 多重值通过沿路径累加 `count` 自然保留出现次数。

### 代码

@include-code(./main.py, python)

### 复杂度

设值域位数为 $B\le20$，建 Trie 与递推均为 $O(nB)$，空间 $O(nB)$。

### 总结

比较 `(a^x) <= k` 时，关键是二进制字典序：在 `k` 的 1 位选择更小异或位后，低位就不再受限制。
