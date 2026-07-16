---
oj: "luogu"
problem_id: "P4735"
title: "最大异或和"
description: "把后缀异或改写为前缀异或区间查询，用可持久化 01-Trie 支持追加与最大异或。"
difficulty: "省选/NOI-"
date: 2026-07-16 19:57
toc: true
tags: ["可持久化Trie", "前缀异或", "在线追加", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4735
---

[[TOC]]

### 题意

序列支持末尾追加。询问在 `l <= p <= r` 中最大化 `a[p] ^ ... ^ a[N] ^ x`。

### 思路

令 `s[i]` 为前 `i` 项异或，则询问式为：

```text
s[p-1] ^ (s[N] ^ x)
```

所以要在前缀下标 `[l-1,r-1]` 中找与固定值异或最大的 `s`。每加入一个前缀异或，就从旧根复制 24 层路径得到新版本；未修改的子树直接共享。

约定 `roots[t]` 包含前缀下标 `0..t-1`。因此查询区间使用 `roots[r] - roots[l-1]` 的节点计数差。每一位优先进入能让异或位为 1 且差分计数大于 0 的儿子。

### Python 知识

- `operation = input().split()` 保留首项为 `bytes`，可直接与 `b"A"` 比较。
- `clone` 同步复制三个紧凑数组中的一个节点。
- `array("i")` 的节点下标和计数足够容纳约 1500 万节点，内存远低于嵌套列表对象。
- 当前总前缀异或只需一个整数变量随追加更新。

### 代码

@include-code(./main.py, python)

### 复杂度

每次追加和询问都处理 24 位，时间 $O((n+m)\cdot24)$；每次追加新建 25 个节点，空间 $O((n+m)\cdot24)$。

### 总结

先把后缀式改写成前缀异或，再用版本差表达下标范围，是可持久化 01-Trie 的标准模型。
