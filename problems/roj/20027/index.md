---
oj: "roj"
problem_id: "20027"
title: "聚会"
description: "二分答案：时间 T 可行等价于每个人的可达区间有公共交点，判定只需比较区间左端点最大值与右端点最小值。"
difficulty: "普及"
date: 2026-09-06 15:54
updated: 2026-10-07 10:45
toc: true
tags: ["二分答案", "数学"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20027
---

[[TOC]]

## 题目描述

数轴上有 $n$ 个人，第 $i$ 个人初始在 $x_i$、速度 $v_i$。选一个实数位置 $p$ 作为聚会点，所有人同时出发，求最晚到达时间的最小值 $\min_{p} \max_{i} |x_i-p|/v_i$。

输入第一行 $n$，第二行 $n$ 个整数 $x_i$，第三行 $n$ 个整数 $v_i$；输出一个浮点数，四舍五入保留 5 位小数。样例：`3 / 7 1 3 / 1 2 1` 输出 `2.00000`。$2 \le n \le 10^5$，$1 \le x_i, v_i \le 10^7$。

## 思路

二分答案。给定时间 $T$，第 $i$ 个人的可达区间是 $[x_i-v_iT,\ x_i+v_iT]$，所有人能同时到达等价于这些区间有公共交点，即左端点最大值 $\le$ 右端点最小值，一次判定 $O(n)$ 且关于 $T$ 单调。实数二分约 100 次即可满足精度。

## 参考代码

@include-code(./main.cpp, cpp)
