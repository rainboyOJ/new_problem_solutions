---
oj: "shumeng"
problem_id: "CSP202603A"
title: 平衡数
description: "逐位统计每个正整数二进制表示中的 0 和 1，数量相等时计数。"
date: 2026-07-31 16:22
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202603A
difficulty: "未知"
---

[[TOC]]

### 题意

如果一个正整数的二进制表示中 `0` 和 `1` 的数量相等，则称它为平衡数，统计给出的 `n` 个数中平衡数的个数。

### 思路

不断取当前数的最低位：最低位为 `1` 就增加 `ones`，否则增加 `zeros`，然后右移一位。循环结束时，恰好统计了从最高位 `1` 开始的全部二进制位；更高位补的 `0` 没有被统计。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每个数最多处理 `O(log a_i)` 位，时间复杂度为 `O(sum log a_i)`，空间复杂度为 `O(1)`。

### 总结

统计二进制位时从数值本身开始右移，就自然跳过了表示中的高位补零。
