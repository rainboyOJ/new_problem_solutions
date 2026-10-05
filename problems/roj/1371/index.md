---
oj: "roj"
problem_id: "1371"
title: "看病"
description: "用大根堆维护排队患者，C++ priority_queue 直接 push / top / pop，每次操作 O(log n)，共 O(n log n)。"
difficulty: "普及-"
date: 2026-09-30 07:29
updated: 2026-10-05 12:23
toc: true
tags: ["堆", "优先队列", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1371
---

[[TOC]]

## 题目描述

医院按病情优先级安排看病。依次处理 $n$ 个操作：`push a b` 表示姓名 `a`、优先级 `b` 的患者加入排队；`pop` 表示取出当前排队中优先级最大的患者，输出其姓名和优先级，若无人排队输出 `none`。所有优先级互不相同。

| 输入样例 | 输出样例 |
| --- | --- |
| `pop` / `push bob 3` / `push tom 5` / `push ella 1` / `pop` / `push zkw 4` / `pop` | `none` / `tom 5` / `zkw 4` |

数据范围：$1 \leqslant n \leqslant 100000$，$0 \leqslant$ 优先级 $\leqslant 2000000000$，姓名为长度小于 20 的小写字母串。

## 思路

只有「插入」和「取最大」两种操作，这是优先队列的标志性场景：用大根堆 `priority_queue<pair<ll, string> >` 维护排队患者，push 入堆，pop 时取堆顶，堆空输出 `none`。每次堆操作 $O(\log n)$，总复杂度 $O(n \log n)$。

## 参考代码

@include-code(./main.cpp, cpp)
