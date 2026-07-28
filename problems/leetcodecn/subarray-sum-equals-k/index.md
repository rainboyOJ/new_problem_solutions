---
oj: "leetcodecn"
problem_id: "subarray-sum-equals-k"
title: "和为 K 的子数组"
description: "前缀和 + 哈希表统计历史前缀出现次数，边扫边累计答案，O(n)。"
difficulty: "中等"
date: 2026-07-28 22:05
toc: true
tags: ["前缀和", "哈希表", "数组", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/subarray-sum-equals-k/
---

[[TOC]]

### 题意

给定整数数组 nums 和整数 k，统计和为 k 的连续子数组的个数。

### 思路

暴力 O(n²) 枚举所有子数组。优化：前缀和 `s[i]` 表示 `[0..i)` 的和，子数组 `[l..r]` 的和为 `s[r+1] - s[l]`。遍历时用哈希表记录每个前缀和出现的次数，对当前位置 `sum`，查 `sum - k` 的出现次数即为以当前位置结尾的合法子数组个数。

注意：先查询后插入，且初始插入 `{0: 1}` 表示空前缀。

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：O(n)，每个元素处理一次。
- 空间复杂度：O(n)，哈希表最多存 n 个前缀和。

### 总结

前缀和配合哈希表是子数组统计问题的标准模型。与两数之和的配对计数本质相同：固定右端点，查历史信息的数量。有负数时双指针失效，但前缀和哈希表仍然正确。
