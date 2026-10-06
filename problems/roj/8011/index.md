---
oj: "roj"
problem_id: "8011"
title: "比赛时间"
description: "把起止两个时刻都换算成自 11 月 1 日 00:00 起的绝对分钟数再相减，差值为负输出 -1，全程 O(1)。"
difficulty: "入门"
date: 2026-10-02 16:59
updated: 2026-10-06 16:51
toc: true
tags: ["输入输出", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/8011
---

[[TOC]]

## 题目描述

毛毛参加一场比赛，比赛从 11 月 11 日上午 11 点 11 分开始。给定结束时刻——11 月第 $D$ 天（$11 \le D \le 14$）的 $H$ 时 $M$ 分（24 小时制），求比赛花费的总分钟数；若结束早于开始，输出 $-1$。输入一行 3 个整数 $D\ H\ M$，输出一个整数。

样例输入：`12 13 14`，样例输出：`1563`。

## 思路

把任意时刻 $(D,H,M)$ 换算成自 11 月 1 日 00:00 起的绝对分钟数 $(D-1)\times1440+H\times60+M$，两时刻同轴相减即花费分钟数。差值为负说明结束早于开始，输出 $-1$，否则原样输出（同刻即 $0$）。

## 参考代码

@include-code(./main.cpp, cpp)
