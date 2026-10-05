---
oj: "luogu"
problem_id: "P8756"
title: "[蓝桥杯 2021 省 AB2] 国际象棋"
description: "把每一列压成二进制状态，利用马只会影响前两列的性质，做记录前两列状态和已放马数量的轮廓 DP。"
difficulty: "提高+/省选-"
date: 2026-06-21 05:26
updated: 2026-10-03 12:38
toc: true
tags: ["状态压缩", "动态规划", "轮廓DP", "计数dp"]
categories: []
pre:
  - oj: "luogu"
    problem_id: "P1879"
    reason: "B 直接复用 A 教的「把一层压成二进制状态、先预处理单层合法状态、再逐层枚举兼容状态做计数 DP」这一整套按层状压步骤，只是层从行变成列、兼容表从 cur&pre==0 换成 ok1/ok2 两张表，并按马的数量多开一维 used。"
  - oj: "luogu"
    problem_id: "P1896"
    reason: "B 直接复用 A 教的『一行/一列压成 bitmask + 用 popcount 累加已放置数量、逐行/逐列计数转移』这一状态设计（B 的 main.cpp 逐列转移时 dp[nxt][p1][cur][nused]=…+bit_cnt[cur]），只是把 A 的单行前驱扩成前两列轮廓、把同行相邻限制换成马的跳列攻击限制，属加维度加约束的台阶式叠加。"
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P8756
---

[[TOC]]

### 题意

在 `N x M` 的棋盘上放 `K` 个马，要求任意两个马都不能互相攻击。
问方案数，对 `1e9+7` 取模。

### 思路

先看一个小数据暴力：

@include-code(./brute.cpp, cpp)

暴力就是逐格枚举放不放马，再检查是否合法。

正解要利用 `N<=6` 很小这一点，把“一整列”压成一个二进制状态。

关键观察是：

- 当前列只会和前一列、前两列发生马的攻击关系
- 更早的列不会再影响当前列

因此状态中只需要记住：

- 前两列的摆放情况
- 已经放了多少个马

设列状态为 `s`。

预处理两种合法性：

- `ok1[a][b]`：相邻两列 `a,b` 是否冲突
- `ok2[a][b]`：相隔两列 `a,b` 是否冲突

然后做按列推进的 DP：

- `dp[col][pre2][pre1][used]`


#### DP 转移方程

枚举当前列状态 `cur`，若它和前两列都不冲突，则：

$$
dp[col+1][pre1][cur][used+popcount(cur)]
\mathrel{+}= dp[col][pre2][pre1][used]
$$

其中合法条件是 `ok1[pre1][cur]` 且 `ok2[pre2][cur]`。

每次枚举当前列状态 `cur`，只要满足：

- `ok1[pre1][cur]`
- `ok2[pre2][cur]`

就能转移。

这就是典型的“小行数、大列数”的轮廓 DP。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度约为 $O(M * 2^{3N} * K)$，但由于 `N<=6`，状态数很小，可以通过。

### 总结

这题的关键是识别马的攻击范围只跨 1 列和 2 列，因此状态只需要保留前两列。
看清这一点后，问题就会自然落到列状压 DP 上。

### 一图流解析

这张图把本题的建模、关键转移、实现检查和训练方法压缩到一页，适合读完正文后复盘。

![一图流解析](./one-page-explainer.png)

