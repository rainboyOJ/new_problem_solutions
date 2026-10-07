---
oj: "roj"
problem_id: "1536"
title: "「一本通 4.1 例 2」数星星 Stars"
description: "利用输入按 y 增序给出的特性将二维偏序降维，使用树状数组维护横坐标前缀和统计星星等级"
difficulty: "普及"
date: 2026-09-30 16:53
updated: 2026-10-06 00:35
toc: true
tags:
  - 树状数组
  - 数据结构
favorite: false
favorite_reason: ""
categories:
  - 数据结构
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1536
---

[[TOC]]

## 题目描述

天空中有 $N$ 颗互不重叠的星星。若某颗星星左下方（含正左、正下）有 $k$ 颗星星，则称它是 $k$ 级的。给定按 $y$ 增序给出（$y$ 相同按 $x$ 增序）的 $N$ 个点，求 $0\sim N-1$ 级各有多少颗星星。

输入第一行 $N$，随后 $N$ 行每行两个整数 $x_i, y_i$；输出 $N$ 行，第 $k+1$ 行是 $k$ 级星星的数目。$1\le N\le 1.5\times10^4$，$0\le x,y\le 3.2\times10^4$。样例输入 `5 / 1 1 / 5 1 / 7 1 / 3 3 / 5 5`，样例输出 `1 / 2 / 1 / 1 / 0`。

## 思路

输入已按 $y$ 增序给出，处理到某颗星星时，此前读入的星星其 $y$ 都不超过它，因此只需统计其中 $x\le x_i$ 的星星数即为该星等级。用树状数组维护各横坐标出现的次数，每颗星星做一次前缀和查询与一次单点加一即可，复杂度 $O(N\log M)$。

## 参考代码

@include-code(./main.cpp, cpp)
