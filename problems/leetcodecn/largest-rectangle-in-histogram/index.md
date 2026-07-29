---
oj: "leetcodecn"
problem_id: "largest-rectangle-in-histogram"
title: "柱状图中最大的矩形"
description: "单调栈弹出时左右第一个更矮位置决定宽度，高度乘宽度即为面积，末尾补 0 清算剩余。"
difficulty: "提高+/省选-"
date: 2026-07-29 12:12
toc: true
tags: ["单调栈", "栈"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/largest-rectangle-in-histogram/
---

[[TOC]]

### 题意
给定柱状图的高度数组，求能勾勒出的最大矩形面积。
### 思路
单调栈保存柱子下标，栈底到栈顶高度递增。弹出时，弹出的高度 `h` 就是被结算柱子的高度，左边界是弹出后新栈顶（第一个更矮的柱），右边界是当前扫描位置 `i`（第一个右边更矮的柱），宽度 = `i - l - 1`。

末尾补一个虚拟的 `0` 高度柱，确保所有栈中剩余柱子都被结算。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
- 时间复杂度：$O(n)$，每个柱子最多入栈出栈一次。
- 空间复杂度：$O(n)$，栈最多存所有下标。
### 总结
柱状图最大矩形是单调栈的经典应用：弹出时左右第一个更矮的位置决定宽度。末尾补 0 是关键技巧，确保结算所有柱子。
