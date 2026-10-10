---
oj: "roj"
problem_id: "2060"
title: "usaco-3.4.4 “破锣摇滚”乐队"
description: "按创作顺序逐首决策，dp[d][u] 表示已开 d 张 CD、最后一张已用 u 分钟时最多可选歌曲数的动态规划。"
difficulty: "普及"
date: 2026-10-01 05:45
updated: 2026-10-06 10:36
toc: true
tags:
  - "动态规划"
  - "背包"
  - "python"
favorite: false
favorite_reason: ""
categories:
  - "动态规划"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2060
---

[[TOC]]

## 题目描述

从 $N$ 首按创作时间排列的歌曲中选出尽量多的歌，依次装入至多 $M$ 张 CD。每张 CD 总时长不超过 $T$，一首歌不能拆分。输入第一行为 $N, T, M$，第二行为 $N$ 个整数表示每首歌长度。

样例输入：

```
4 5 2
4 3 4 2
```

样例输出：

```
3
```

## 思路

顺序固定，只需记录当前已开 CD 数 $d$ 与最后一张 CD 已用分钟 $u$。对每首歌枚举三种选择：丢弃、接在最后一张 CD 末尾、另开一张新 CD，保留歌曲数更多的状态。数据范围 $N,M,T \le 20$，直接做 $dp[d][u]$ 即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)

