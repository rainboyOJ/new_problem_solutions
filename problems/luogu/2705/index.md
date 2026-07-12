---
oj: "luogu"
problem_id: "P2705"
title: "小球"
description: "比较每交换一对红蓝球带来的固定收益，决定是否交换到上限。"
difficulty: "入门"
date: 2026-06-18 20:52
toc: true
tags: ["数学", "贪心"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2705
---

[[TOC]]

### 题意

有 `R` 个红盒子、`B` 个蓝盒子，以及对应数量的红球和蓝球。
同色放置分别得 `C`、`D` 分，异色放置都得 `E` 分。
要求求出最大总得分。

### 思路

先看一个可以直接验证想法的朴素解：

可以枚举交换了多少对红蓝球，直接计算每种方案的得分。

@include-code(./brute.cpp, cpp)

关键在于：每多交换 1 对红蓝球，得分变化始终是固定的：

```text
2E - C - D
```

所以只要看这个值的正负：

- 如果大于 0，就尽量多换；
- 如果小于等于 0，就一个都不换。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

主解只做常数次计算，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

这题的本质是一个“每次操作收益固定”的贪心判断。
