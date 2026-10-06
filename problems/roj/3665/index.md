---
oj: "roj"
problem_id: "3665"
title: "直播获奖"
description: "成绩值域只有 0 到 600，用桶计数实时统计各分数人数，再从高分档向低分档累加到计划获奖人数，即得即时分数线。"
difficulty: "普及-"
date: 2026-10-02 14:22
updated: 2026-10-06 16:15
toc: true
tags: ["python", "桶计数", "计数"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common:
  - oj: "luogu"
    problem_id: "P7072"
    reason: "洛谷上的同一道题（CSP-J 2020），其题解改用树状数组做第 k 小查询，可与本文的桶扫描对照"
recommend: []
source: https://roj.ac.cn/problem/3665
---

[[TOC]]

## 题目描述

依次公布 $n$ 个成绩（每个为 $0..600$ 的整数），另有获奖百分比 $w$（$1 \le w \le 99$）。每公布第 $p$ 个成绩，立刻输出当时的获奖分数线：计划获奖人数 $k_p = \max(1, \lfloor p \cdot w / 100 \rfloor)$，把已公布的 $p$ 个成绩从大到小排列，第 $k_p$ 个成绩即为分数线；成绩相同者并列获奖。数据范围：$n \le 10^5$，成绩 $\le 600$。

## 思路

成绩值域只有 $0..600$，用桶 `cnt[s]` 实时统计各分数人数，每读入一个成绩就入桶。查询时从 $600$ 分往低分累加人数，累加和首次达到 $k_p$ 的那一档就是分数线。全程整数运算，避免浮点误差。

## 参考代码

@include-code(./main.cpp, cpp)
