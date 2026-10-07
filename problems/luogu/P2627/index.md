---
oj: "luogu"
problem_id: "P2627"
title: "[USACO11OPEN] Mowing the Lawn G"
description: "枚举最后一个不选的断点，把 DP 转移化为窗口最大值并用单调队列维护。"
difficulty: "普及+/提高"
date: 2026-01-05 10:39
updated: 2026-10-06 07:45
toc: true
tags: ["动态规划", "单调队列", "前缀和"]
categories: []
pre:
  - oj: "luogu"
    problem_id: "P2032"
    reason: "B 沿用 A 的单调队列窗口最值原语，把候选换成 dp[j-1]-S[j] 做 DP 优化，再叠加断点建模与初始断点入队"
  - oj: "luogu"
    problem_id: "P1440"
    reason: "B 把 A 的单调队列取窗内最值步骤用于 dp[j-1]-S[j] 的滑窗最大值，逐断点转移求最大效率和"
  - oj: "luogu"
    problem_id: "P1714"
    reason: "B 的转移 dp[i]=S[i]+max(dp[j-1]-S[j]) 复用 A 教的「递增单调队列维护滑窗内前缀式最值、先删过期队头再算答案」这一步，只是队列里存的量从前缀和换成 dp[j-1]-S[j] 并由求最小换成求最大"
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2627
---

[[TOC]]

### 题意

有 `n` 只奶牛排成一排，第 `i` 只奶牛效率为 `e[i]`。可以选择一些奶牛获得效率和，但不能选择超过 `k` 只连续的奶牛。求最大效率和。

### 思路

一个直接 DP 是：令 `dp[i]` 表示考虑前 `i` 只奶牛的最大效率，然后枚举末尾连续选了多少只。

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

把“末尾连续选了多少只”换成“最后一个不选的位置 `j`”更好写。若最后一个不选的位置为 `j`，那么 `j+1..i` 全部选中，长度要求 `i-j <= k`，贡献为：

```text
dp[j-1] + S[i] - S[j]
```

其中 `S` 是前缀和。于是：

```text
dp[i] = S[i] + max(dp[j-1] - S[j])    (i-k <= j <= i)
```

对固定的 `i`，`S[i]` 是常数，只需要找窗口 `[i-k, i]` 中 `dp[j-1]-S[j]` 的最大值。这个窗口随 `i` 单调右移，因此用单调队列维护断点 `j` 即可。

注意 `j=0` 表示前面没有断点，可以从第 `1` 只开始连续选择。这个初始断点必须先放入队列。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度 $O(n)$，每个断点最多入队和出队一次。

空间复杂度 $O(n)$。

### 总结

本题的重点是把“连续不超过 `k` 个”转成“枚举最后一个不选的位置”。整理出 `S[i] + max(dp[j-1]-S[j])` 后，单调队列优化就很自然。
