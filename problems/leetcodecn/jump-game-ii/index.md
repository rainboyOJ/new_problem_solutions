---
oj: "leetcodecn"
problem_id: "jump-game-ii"
title: "跳跃游戏 II"
description: "BFS 层次遍历思想：当前层边界与下一层最远位置确定跳跃次数。"
difficulty: "普及+/提高"
date: 2026-07-29 12:27
toc: true
tags: ["贪心", "数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/jump-game-ii/
---

[[TOC]]

### 题意
给定跳跃数组（保证可达），求最少跳跃次数。

### 思路
用 BFS 层次遍历的思想：每跳一步，当前"层"的范围是 `[l, r]`，下一层最远可达 `next = max(i + nums[i])` for `i` in `[l, r]`。当 `r` 到达末尾时停止。

每层对应一次跳跃，`next` 是下一层的右边界。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n)$。
- 空间复杂度：$O(1)$。

### 总结
最少跳跃次数 = BFS 层数。每层扩展最远可达位置，贪心选择下一层边界。与跳跃游戏 I 的区别是：I 只判断可达性，II 要最小化步数。
