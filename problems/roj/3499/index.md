---
oj: "roj"
problem_id: "3499"
title: "[noip2000-普及] 税收与补贴问题"
description: "逐价位建立关于补贴额 t 的一次不等式，取上下界交集后在可行区间中选绝对值最小的整数。"
difficulty: "普及"
date: 2026-10-02 03:29
updated: 2026-10-06 12:12
toc: true
tags: ["数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3499
---

[[TOC]]

## 题目描述

已知商品成本 $c$、成本价位销量 $s_0$ 与若干（价位，销量）点，相邻已知点间销量线性变化；超过最高已知价位后，每涨 1 元销量减少 $d$。设政府预期价为 $P$，政府对每件商品收税或补贴整数 $t$（$t>0$ 为补贴，$t<0$ 为收税），总利润 $=($价位 $-c+t)\times$ 销量。求使 $P$ 处总利润最大的最小 $|t|$；不存在则输出 `NO SOLUTION`。

## 思路

每个可售价位 $p$ 都给出一个关于 $t$ 的一次不等式，按销量系数大小分别得到 $t$ 的下界、上界或无解判定；逐价位扫描并维护可行区间 $[lo,hi]$，最后在其中取绝对值最小的整数。

## 参考代码

@include-code(./main.cpp, cpp)
