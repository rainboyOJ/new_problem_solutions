---
oj: "luogu"
problem_id: "P1470"
title: "[IOI 1996 / USACO2.3] 最长前缀 Longest Prefix"
description: "用前缀可达性 DP 判断序列能否由原串重复拼成，后缀是否为词用哈希集合或倒序 Trie 查询。"
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

令 `dp[i]` 表示前缀 `S[0..i)` 能否由词集完整拆开，边界 `dp[0]=true`。

转移时枚举最后一个词的长度 `len`：若后缀 `S[i-len..i)` 是一个词，且 `dp[i-len]` 为真，则 `dp[i]=true`。词长最多 10，所以从 `i` 往回最多尝试 10 个长度，而不是遍历全部原串。

“后缀是否是词”有两种查询方式：

- 哈希：`hash.cpp` 直接用 `unordered_set` 存词，构造子串后查询，实现最简单。
- 有序集合：`set.cpp` 用 `set<string>` 存词，查询 `O(log |P|)` 次字符串比较；词集只有 200 个、词长不超过 10，开销可忽略。
- 倒序 Trie：`trie.cpp` 把每个词反着插入，让 `S` 从 `i` 往回走，边走边判断；走不动时说明不存在更长的候选词，直接剪枝。

注意 `dp[i]` 并不是单调的（例如 `i` 可达不代表 `i+1` 可达），所以答案要取所有可达位置的最大值。

### Python 知识

- `tokens.index(b".")` 找到原串区与目标串的分隔符。
- `defaultdict(set)` 同时完成按长度分组和去重。
- `b"".join(...)` 拼回跨多行输入的目标序列。
- `bytearray(n+1)` 是紧凑的布尔 DP 数组。

### 代码

@include-code(./main.py, python)

哈希查询版本的 C++ 实现：

@include-code(./hash.cpp, cpp)

有序集合版本的 C++ 实现：

@include-code(./set.cpp, cpp)

倒序 Trie 版本的 C++ 实现：

@include-code(./trie.cpp, cpp)

### 复杂度

最多 10 种长度，时间 $O(10|S|)$ 加短字符串哈希成本，空间 $O(|S|+|P|)$。

### 总结

“按长度分组为集合”是 Python 处理许多短模式串时很实用的优化。
