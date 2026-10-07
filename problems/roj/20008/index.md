---
oj: "roj"
problem_id: "20008"
title: "唱K"
description: "神曲最长必放最后，问题化为容量 t-1、先比首数再比总长的 0/1 背包。"
difficulty: "普及-"
date: 2026-10-02 19:36
updated: 2026-10-06 02:18
toc: true
tags: ["动态规划", "背包", "01背包", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20008
---

[[TOC]]

## 题目描述

KTV 还剩 $t$ 秒，有 $n$ 首普通歌和一首 678 秒的神曲《阿什尼亚克西》；到点时若还有歌在唱就等它唱完，故每首歌都须在 $t-1$ 秒前开唱。输入第一行 $n,t$（$n\le 50$，$t\le 10^9$），第二行 $n$ 首普通歌的长度（不超过 3 分钟）；输出总首数（含神曲）与总时长，先让首数最多，再在此前提下让总时长最大。样例输入 `3 100 / 60 70 80`，输出 `2 758`。

## 思路

神曲 678 秒最长，放最后唱最优，顺序问题消失，只需选普通歌使总和 $\le t-1$。以 $f[s]$ 记恰好凑出总长 $s$ 的最多首数做 0/1 背包，容量收窄到歌长总和（不足 9000）以免 $t$ 过大；先取最大首数，再在同首数里取最大总长。

## 参考代码

@include-code(./main.cpp, cpp)
