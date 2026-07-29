---
oj: "leetcodecn"
problem_id: "jump-game"
title: "跳跃游戏"
description: "维护最远可达位置，扫描时不断扩展，若中途无法前进则不可达。"
difficulty: "普及/提高-"
date: 2026-07-29 12:26
toc: true
tags: ["贪心", "数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/jump-game/
---

[[TOC]]

### 题意
给定跳跃数组，判断能否到达末尾。

### 思路
维护 `max_reach` 表示当前最远可达位置。扫描到 `i` 时，若 `i > max_reach` 说明无法到达位置 `i`，返回 false。否则更新 `max_reach = max(max_reach, i + nums[i])`。

`max_reach` 是单调不减的扫描不变式：每个可达位置都能进一步扩展可达范围。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n)$。
- 空间复杂度：$O(1)$。

### 总结
跳跃可达性判断是贪心的典型：最远可达位置单调不减，扫描一遍即可。无需回溯或动态规划。
