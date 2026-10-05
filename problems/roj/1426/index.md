---
oj: "roj"
problem_id: "1426"
title: "「一本通 1.1 例 5」智力大冲浪"
description: "反悔贪心：按期限排序逐个安排，堆里存已安排游戏的扣款数，放不下就弹出扣款最小的（记为超期），未被安排的扣款总和最小即最优。"
difficulty: "普及-"
date: 2026-07-05 21:47
updated: 2026-10-05 23:22
toc: true
tags:
  - 贪心
  - 堆
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1426
---

[[TOC]]

## 题目描述

有 $n$ 个游戏（$n \leqslant 500$），第 $i$ 个游戏必须在第 $t_i$ 个时段结束前完成（$1 \leqslant t_i \leqslant n$），每个时段只能完成一个游戏。未按期完成第 $i$ 个游戏会损失 $w_i$ 元（$w_i$ 为自然数）。初始有 $m$ 元奖励，求合理安排后能保留的最多的钱（即最小化总扣款）。

## 思路

按期限从小到大排序，逐个尝试安排游戏，用小根堆维护已安排游戏的扣款数。若堆的大小超过当前期限，说明时段不够，弹出扣款最小的游戏（记为超期）。最终堆里保住的扣款总和最大，答案为 $m - (\sum w_i - \text{堆中总和})$。

## 参考代码

@include-code(./main.cpp, cpp)
