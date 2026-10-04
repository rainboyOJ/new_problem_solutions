---
oj: "roj"
problem_id: "1264"
title: "合唱队形"
description: "以每个位置为峰值，正向 LIS 得左段、反向 LIS 得右段，rise[i]+fall[i]-1 的最大值即最多保留人数，N 减之即为答案。"
difficulty: "普及-"
date: 2026-09-30 02:25
updated: 2026-10-05 07:28
toc: true
tags:
  - DP
  - LIS
  - 动态规划
favorite: false
favorite_reason: ""
categories:
  - 动态规划
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1264
---

[[TOC]]

## 题目描述

$N$ 位同学排成一排，老师想让其中的 $(N-K)$ 位出列，使剩下的 $K$ 位同学身高呈“先严格上升、后严格下降”的合唱队形。给定 $N$ 和各位同学的身高，求最少需要出列的同学数。$2 \le N \le 100$，$130 \le T_i \le 230$。

输入第一行为 $N$，第二行为 $N$ 个身高；输出一行，为最少出列人数。

样例输入：

```
8
186 186 150 200 160 130 197 220
```

样例输出：

```
4
```

## 思路

以每个位置 $i$ 为峰值，左段是以 $i$ 结尾的最长严格上升子序列 `rise[i]`，右段等价于把序列反转后求一次同样的严格上升子序列 `fall[i]`。峰值被算了两次，所以最多保留人数为 $\max_i\big(\text{rise}[i]+\text{fall}[i]-1\big)$，答案为 $N$ 减去该值。

## 参考代码

@include-code(./main.cpp, cpp)
