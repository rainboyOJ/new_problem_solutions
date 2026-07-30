---
oj: "noi_openjudge"
problem_id: "ch0105-45"
title: "金币"
description: "按每天工资等于连续发放天数的分段规则，逐段累加金币。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "循环", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/45/
---

[[TOC]]

### 题意

第 $i$ 个发薪阶段持续 $i$ 天，每天发 $i$ 枚金币。求前给定天数内收到的金币总数。

### 思路

变量 `salary` 同时表示本阶段每天的金币数和本阶段长度。当前剩余天数可能不足一个完整阶段，因此本阶段实际发放天数为 `min(days, salary)`。

加入 `salary * paid_days` 后扣除已处理天数，并进入下一阶段。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

处理到第 $k$ 个阶段时已覆盖约 $k^2/2$ 天，故时间复杂度为 $O(\sqrt n)$，额外空间复杂度为 $O(1)$。

### 总结

按规则天然分段的模拟题，直接处理整段比逐天累加更容易表达边界。
