---
oj: "roj"
problem_id: "1423"
title: "「一本通 1.1 例 2」种树"
description: "按区间右端点升序排序，区间缺树时贪心靠右侧放置以最大化后续重叠复用。"
difficulty: "普及"
date: 2026-09-30 09:25
updated: 2026-10-05 23:22
toc: true
tags:
  - 贪心
  - 区间问题
favorite: false
favorite_reason: ""
categories:
  - 贪心
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1423
---

[[TOC]]

## 题目描述

编号 $1 \sim N$ 的地块每块最多种一棵树，$M$ 个需求各给出 $B, E, T$，要求区间 $[B,E]$ 内至少种 $T$ 棵树（区间可交叉）。求最少种多少棵，并输出每棵树的位置。

## 思路

经典区间贪心：把所有区间按右端点 $E$ 升序排序，逐个统计区间内已有的树数，不足则从右端点向左补种到空位置上。因为后面处理的区间右端点都不小于当前区间，靠右种树最容易被后续区间复用，所以总量最少。

## 参考代码

@include-code(./main.cpp, cpp)
