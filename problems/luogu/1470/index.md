---
oj: "luogu"
problem_id: "P1470"
title: "[IOI 1996 / USACO2.3] 最长前缀 Longest Prefix"
description: "按原串长度分组，用可达位置 DP 判断序列前缀能否由原串重复拼成。"
difficulty: "普及/提高-"
date: 2026-07-16 19:57
toc: true
tags: ["动态规划", "字符串", "defaultdict", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1470
---

[[TOC]]

### 题意

给定最多 200 个短原串，它们可以重复使用。求目标序列能由这些原串拼出的最长前缀长度。

### 思路

令 `reachable[i]` 表示长度为 `i` 的前缀可以拼出。若 `i` 可达，检查从 `i` 开始的子串是否属于某种原串；匹配长度为 `length` 时令 `reachable[i+length]=1`。

原串长度最多 10。先按长度分成集合后，每个可达位置最多只做 10 次切片和集合查询，而不是遍历 200 个原串。

### Python 知识

- `tokens.index(b".")` 找到原串区与目标串的分隔符。
- `defaultdict(set)` 同时完成按长度分组和去重。
- `b"".join(...)` 拼回跨多行输入的目标序列。
- `bytearray(n+1)` 是紧凑的布尔 DP 数组。

### 代码

@include-code(./main.py, python)

### 复杂度

最多 10 种长度，时间 $O(10|S|)$ 加短字符串哈希成本，空间 $O(|S|+|P|)$。

### 总结

“按长度分组为集合”是 Python 处理许多短模式串时很实用的优化。
