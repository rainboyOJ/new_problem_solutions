---
oj: "luogu"
problem_id: "P2887"
title: "[USACO07NOV] Sunscreen G"
description: "按 SPF 升序扫描防晒霜，用小根堆优先匹配 maxSPF 最小、最快过期的奶牛。"
difficulty: "普及/提高-"
date: 2026-06-22 21:13
toc: true
tags: ["贪心", "堆", "区间覆盖", "排序"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2887
---

[[TOC]]

### 题意

每头奶牛能接受一个 SPF 区间 `[minSPF,maxSPF]`。

每种防晒霜有固定 SPF 和若干瓶。每瓶只能给一头奶牛用。

求最多能满足多少头奶牛。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

暴力可以把每瓶防晒霜展开成一个点，再跑二分图最大匹配。正解使用更直接的贪心。

按 SPF 从小到大处理防晒霜。当前 SPF 下，所有 `minSPF <= SPF` 的奶牛才可能使用它，把这些奶牛加入候选集合。

候选集合中，如果 `maxSPF < SPF`，说明这头奶牛已经无法使用当前以及后续更大的 SPF，直接丢弃。

剩下的奶牛里，应该优先满足 `maxSPF` 最小的奶牛。因为它最容易在后面过期；如果当前不给它用，未来只会更难。

所以用小根堆维护候选奶牛的 `maxSPF`，每瓶防晒霜匹配堆顶。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

排序和堆操作总复杂度约为：

```text
O((C+L+总瓶数) log C)
```

空间复杂度为 $O(C+L)$。

### 总结

本题的贪心重点是“谁最急”。

按 SPF 递增扫描时，`maxSPF` 最小的奶牛最容易失去机会，所以每次都优先满足它。
