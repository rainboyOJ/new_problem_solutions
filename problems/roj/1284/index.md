---
oj: "roj"
problem_id: "1284"
title: "摘花生"
description: "网格只能向东、向南走，到达每格的最大收获只由上方与左方两格决定，线性 DP 一维滚动数组 O(RC) 直接推进到东南角。"
difficulty: "入门"
date: 2026-09-30 03:14
updated: 2026-10-05 08:04
toc: true
tags:
  - "动态规划"
  - "网格 DP"
  - "线性 DP"
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1284
---

[[TOC]]

## 题目描述

Hello Kitty 想摘点花生送给她喜欢的米老鼠。她来到一片 $R \times C$ 的网格状花生地（$1 \leqslant R, C \leqslant 100$），从西北角进去、东南角出来，只能向东或向南走，不能向西或向北走。每个交叉点上有一株花生苗（$0 \leqslant M \leqslant 1000$），经过就能摘走上面的全部花生。输入第一行是整数 $T$（$1 \leqslant T \leqslant 100$），每组数据第一行是 $R$ 和 $C$，随后 $R$ 行每行 $C$ 个整数，按从北向南、从西向东的顺序给出每株花生苗上的花生数；对每组数据输出一行，即最多能摘到的花生颗数。

样例：输入 $2$ 组——第一组 $R=2, C=2$，两行为 `1 1` 和 `3 4`，输出 `8`；第二组 $R=2, C=3$，两行为 `2 3 4` 和 `1 6 5`，输出 `16`（走 $2 \to 3 \to 6 \to 5$）。

## 思路

由于只能向东、向南走，到达格子 $(i,j)$ 的最后一步只能来自上方或左方；设 $dp[i][j]$ 为走到该格能摘到的最大花生数，则 $dp[i][j] = M_{i,j} + \max(dp[i-1][j],\ dp[i][j-1])$，边界外视为 $0$。逐行逐格递推到东南角即得答案；实现时用一维数组原地滚动——更新前 $dp[j]$ 是上一行的答案（来自上方）、$dp[j-1]$ 已是本行的答案（来自左方），空间降为 $O(C)$。

## 参考代码

@include-code(./main.cpp, cpp)
