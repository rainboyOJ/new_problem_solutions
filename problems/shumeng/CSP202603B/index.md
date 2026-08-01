---
oj: "shumeng"
problem_id: "CSP202603B"
title: 机器人项目管理
description: "灵活任务按单位咖啡收益率排序，普通任务用 0/1 背包选择，再合并两类任务的最大收益。"
date: 2026-07-31 16:22
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202603B
difficulty: "未知"
---

[[TOC]]

### 题意

每个任务有初始耗时。灵活型任务可以使用 `0` 到 `a_i` 杯任意实数咖啡，使用满杯时减少 `b_i`；普通型任务只能使用 `0` 杯或 `a_i` 杯。总咖啡数不超过 `m`，求最小总耗时。

### 思路

灵活型任务的每杯收益恒为 `b_i/a_i`。因此固定给灵活型任务 `x` 杯咖啡时，应按 `b_i/a_i` 从大到小填充，得到 `flexible_gain[x]`。

普通型任务只能整件选择。设 `dp[x]` 为使用恰好 `x` 杯咖啡从普通任务获得的最大减少量，用 0/1 背包转移。最后枚举普通任务使用的杯数 `x`，把剩余的 `m-x` 杯交给灵活任务，取最大总减少量。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

排序后，计算灵活型收益表的复杂度为 `O(nm)`，普通型 0/1 背包为 `O(nm)`，空间复杂度为 `O(m)`。

### 总结

连续可分配的任务先按单位收益率贪心处理；只能整件选择的任务再用背包处理，最后枚举两类任务之间的资源分配。
