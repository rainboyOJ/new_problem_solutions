---
oj: "leetcodecn"
problem_id: "combination-sum"
title: "组合总和"
description: "回溯枚举每个候选数选或不选、选几次，允许重复使用当前数后再推进到下一个候选数。"
difficulty: "普及+/提高"
date: 2026-07-29 11:20
toc: true
tags: ["回溯", "枚举", "递归"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/combination-sum/
---

[[TOC]]

### 题意

给定无重复元素的整数数组 `candidates` 和目标整数 `target`，找出所有和为 `target` 的组合。同一个候选数可以无限重复选取。不同组合以至少一个数字的选取数量不同来区分。

### 思路

最直接的思路是枚举每个候选数的使用次数，形成一条选择序列后检查总和是否等于 `target`：

@include-code(./brute.cpp, cpp)

这个暴力用 `cnt[i]` 记录每个候选数的选取次数，递归到所有候选数决定完毕后再检查总和。它在小数据上可靠，但当候选数多或目标值大时分支爆炸。

优化的关键是：在递归过程中直接维护剩余值 `left`，若 `left < 0` 立即剪枝返回；同时用"选/不选"的二元分支结构——`dfs(i+1, left)` 表示跳过 `candidates[i]`，`dfs(i, left - candidates[i])` 表示使用一次 `candidates[i]` 且不推进下标（允许重复使用）。

用起始下标而非从 0 开始，保证组合内部有序，避免产生重复组合（如 `[2,3]` 和 `[3,2]`）。排序候选数后还可以进一步剪枝：若 `left < candidates[i]`，后续更大的候选数也无法命中，直接停止。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：取决于方案数，最坏情况所有组合都合法时为 $O(2^t)$，实际远小于此。
- 空间复杂度：$O(k)$，递归栈深度最多等于候选数个数，`cur` 长度最多等于组合长度。

### 总结

组合枚举题的关键是避免重复组合。用起始下标 `i` 控制"只往后选"，同一候选数可以重复使用时不推进下标（`dfs(i, ...)`），不再使用时推进（`dfs(i+1, ...)`）。剪枝条件 `left < 0` 和排序后的 `left < candidates[i]` 能显著减少无效递归。
