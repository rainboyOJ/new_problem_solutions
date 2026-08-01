---
oj: "shumeng"
problem_id: "CSP202605B"
title: 机器人宿管指南
description: "模拟固定天数的苹果消耗过程，并对机器人数量二分答案。"
date: 2026-07-31 16:22
toc: true
tags: ["二分答案", "模拟", "单调性"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202605B
difficulty: "未知"
---

[[TOC]]

### 题意

初始有 `n` 个苹果。每天先丢弃按比例变质的苹果，再让每个机器人吃一个苹果。求至少支撑 `m` 天时最多的机器人数量。

### 思路

固定机器人数量 `x` 后，可以直接模拟 `m` 天。当天苹果数为 `t` 时，变质数量为 `ceil(t*k/100)`，剩余苹果不足 `x` 就说明无法支撑。

机器人数量越大越难满足条件，因此可行性具有单调性。对 `[0,n]` 二分，检查中点并保留最大的可行值。用 `(t*k+99)/100` 整数计算向上取整。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

二分进行 `O(log n)` 次检查，每次模拟 `m` 天，时间复杂度为 `O(m log n)`，空间复杂度为 `O(1)`。

### 总结

把每天的过程封装成可行性检查后，资源数量问题就变成了标准的单调性二分。
