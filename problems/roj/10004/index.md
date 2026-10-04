---
oj: "roj"
problem_id: "10004"
title: "面试"
description: "四轮评分按优先级判定：先淘汰出现 D 或两个 C 的人，通过者中无 D 且 A 达三个给 sp offer，其余给 offer。"
difficulty: "入门"
date: 2026-10-02 17:24
updated: 2026-10-04 21:37
toc: true
tags: ["入门", "条件判断", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/10004
---

[[TOC]]

## 题目描述

每人四轮面试，每轮评分 A/B/C/D 之一：出现一次 `D` 或两次 `C` 就失败；没有 `D` 且至少三个 `A` 得 special offer；其余得普通 offer。

输入第一行 $T$，之后 $T$ 行每行一个长度 4 的评分串；输出每人的结果 `failed` / `offer` / `sp offer`。样例：输入 `2`、`AAAB`、`ADAA`，输出 `sp offer`、`failed`。

## 思路

结果只由 A、C、D 的个数决定，与位置无关，逐串统计即可。判定必须按优先级：先淘汰（有 `D` 或 `C` 至少两个），再判无 `D` 且 `A` 至少三个给 `sp offer`，否则给 `offer`。顺序不能颠倒，否则 `AAAD` 这类有三个 A 却带 D 的串会被误判成 special offer。

## 参考代码

@include-code(./main.cpp, cpp)
