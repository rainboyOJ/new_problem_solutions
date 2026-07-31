---
oj: "shumeng"
problem_id: "CSP201703A"
title: "分蛋糕"
description: "按蛋糕编号顺序累计每位朋友拿到的重量，达到 k 就开始下一组。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "贪心"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201703A
---

[[TOC]]

### 题意

蛋糕必须按编号顺序依次分配给排队的朋友。每位朋友拿到的总重量达到至少 `k` 后，下一位朋友才开始领取；若最后还剩蛋糕，即使总重量不足 `k`，也由一位朋友拿走。求最终拿到蛋糕的朋友数。

### 思路

直接按题意逐个朋友模拟即可：从当前最小编号的蛋糕开始不断累加，达到 `k` 或蛋糕分完时，这位朋友的分配结束。

@include-code(./brute.cpp, cpp)

不需要真的保存每一组。扫描每块蛋糕时维护当前朋友已经拿到的 `current_weight`：加入本块后若不少于 `k`，答案加一并把累计重量清零。扫描结束后，若累计重量非零，说明最后还有一位朋友拿走了不足 `k` 的剩余蛋糕，再加一。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

分组边界恰好是前缀和第一次达到 `k` 的位置。最后一组不必达到 `k`，只要还有蛋糕就必须计入答案。
