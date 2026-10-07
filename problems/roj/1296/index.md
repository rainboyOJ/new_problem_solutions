---
oj: "roj"
problem_id: "1296"
title: "开餐馆"
description: "以每个地点作为最后一家店做线性 DP，转移时取满足距离大于 k 的前驱中最优的利润，答案取所有收尾位置的最大值。"
difficulty: "普及-"
date: 2026-09-30 03:41
updated: 2026-10-05 08:10
toc: true
tags: ["动态规划", "递推", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1296
---

[[TOC]]

## 题目描述

直线上有 $n$ 个可选地点，位置 $m_1 < m_2 < \dots < m_n$（升序给出），在 $m_i$ 开店的利润为 $p_i$；要选一些地点开餐馆，使任意两家餐馆的距离大于 $k$，求最大总利润。输入第一行为测试组数 $T$，每组数据 3 行：$n$ 与 $k$、$n$ 个升序位置、$n$ 个利润，输出每组数据的最大利润。范围：$1 \leqslant T \leqslant 1000$，$n < 100$，$0 < k < 1000$，$0 < m_i < 10^6$，$0 < p_i < 1000$，均为整数。下面样例中两组数据分别输出 40 和 30：

```text
2
3 11
1 2 15
10 2 30
输出:
40
30
```

## 思路

定义 $dp[i]$ 为以第 $i$ 个地点作为最后一家店时的最大利润；由于位置升序，「任意两家距离大于 $k$」等价于每对相邻被选的店距离大于 $k$，所以转移为 $dp[i] = p_i + \max\bigl(0,\ \max_{j<i,\ m_i-m_j>k} dp[j]\bigr)$。答案取 $\max_i dp[i]$，因为最后一家店不一定开在最右边。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
