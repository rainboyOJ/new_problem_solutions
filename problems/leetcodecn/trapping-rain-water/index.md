---
oj: "leetcodecn"
problem_id: "trapping-rain-water"
title: "接雨水"
description: "双指针维护左右最高柱，较矮侧水量可立即确定，O(n) 时间 O(1) 空间。"
difficulty: "提高+/省选-"
date: 2026-07-28 22:05
toc: true
tags: ["双指针", "栈", "动态规划", "数组", "cpp", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/trapping-rain-water/
---

[[TOC]]

### 题意

给定 n 个非负整数表示柱状图高度，计算能接多少雨水。

### 思路

每个位置能接的水量 = min(左边最高柱, 右边最高柱) - 自身高度。

暴力 O(n²) 每位置独立查左右最大值。优化方法有三种：

1. **前后缀最大值**：预计算 left_max 和 right_max，O(n) 空间。
2. **单调栈**：按凹槽结算，遇到更高的柱子就弹出结算。
3. **双指针**：左右指针各维护一个当前最高柱，较矮侧的水量可立即确定，并移动该侧指针。无需额外数组。


### 代码

@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度

- 时间复杂度：O(n)，双指针各遍历一次。
- 空间复杂度：O(1)，只使用几个变量。

### 总结

双指针解法的核心不变量是：`lmax` 是 `[0..l]` 的最大值，`rmax` 是 `[r..n-1]` 的最大值。`height[l] < height[r]` 时，`lmax < rmax` 不一定成立，但左侧水量由 `lmax` 决定已足够，因为 `rmax` 至少为 `height[r]`，而 `height[r] > height[l]` 保证了右侧有足够高的墙。
