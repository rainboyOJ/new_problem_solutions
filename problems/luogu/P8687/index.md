---
oj: "luogu"
problem_id: "P8687"
title: "[蓝桥杯 2019 省 A] 糖果"
description: "把每包糖果压成一个口味集合 mask，设 dp[mask] 为覆盖这些口味所需的最少包数，做集合覆盖型状压 DP。"
difficulty: "普及/提高-"
date: 2026-06-21 05:09
toc: true
tags: ["状态压缩", "动态规划", "集合覆盖", "位运算"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P8687
---

[[TOC]]

### 题意

有 `N` 包糖果，`M` 种口味。

每包糖果里有若干颗糖，给出了这些糖的口味。
要求最少买几包，才能覆盖全部 `M` 种口味。

### 思路

先看一个只适合小数据验证的暴力：

@include-code(./brute.cpp, cpp)

`brute.cpp` 把每包糖果看成一个 01 选择：`choose_pack[i] = 0/1` 表示不买或买。递归先生成完整选择，叶子节点再检查这些包的并集能不能覆盖全部口味，并统计最少购买数量。

正解的关键是：虽然糖果包数 `N` 不小，但口味数 `M<=20` 很小。

所以不要围绕“选哪些包”设计状态，而要围绕“已经覆盖了哪些口味”设计状态。

把每包糖果压成一个二进制集合：

- 第 `i` 位为 `1` 表示已经覆盖了第 `i` 种口味

设：

- `dp[mask]` 表示覆盖到 `mask` 这些口味时，最少需要买多少包

如果当前考虑一包糖果 `pack_mask`，那么就有转移：

`mask -> mask | pack_mask`


#### DP 转移方程

买第 `i` 包糖果时，设这一包覆盖的口味集合为 `pack_mask[i]`：

$$
dp[mask \mid pack\_mask[i]]
=\min(dp[mask \mid pack\_mask[i]],\ dp[mask]+1)
$$

初始状态是 `dp[0]=0`，答案是 `dp[(1<<M)-1]`。

因为买下这包之后，口味集合只会做一个按位或。

这就是一个很标准的集合覆盖型状压 DP。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度 $O(N 2^M)$，空间复杂度 $O(2^M)$。

### 总结

这题的核心是盯住真正小的量：不是 `N`，而是 `M`。
一旦识别出这一点，题目就会自然转成状压 DP。
