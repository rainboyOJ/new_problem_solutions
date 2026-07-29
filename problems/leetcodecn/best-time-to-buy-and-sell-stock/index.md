---
oj: "leetcodecn"
problem_id: "best-time-to-buy-and-sell-stock"
title: "买卖股票的最佳时机"
description: "扫描时只用此前最低价计算今天卖出的收益，取最大值。"
difficulty: "普及-"
date: 2026-07-29 12:25
toc: true
tags: ["贪心", "数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
---

[[TOC]]

### 题意
给定每日股价，求一次买卖的最大利润。

### 思路
扫描到第 `i` 天时，只需知道前 `i-1` 天的最低价 `min_price`，今天卖出的利润就是 `prices[i] - min_price`。更新 `min_price` 和最大利润即可。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n)$。
- 空间复杂度：$O(1)$。

### 总结
只需维护一个变量"此前最低价"，每步计算当天卖出的利润。贪心正确性：最大利润一定在某天卖出，而最优买入日一定是此前最低价日。
