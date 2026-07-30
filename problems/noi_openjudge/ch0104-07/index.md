---
oj: "noi_openjudge"
problem_id: "ch0104-07"
title: "收集瓶盖赢大奖"
description: "任一瓶盖数量达到对应门槛即可兑换，用 or 判断。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0104/07/
---

[[TOC]]

### 题意

幸运瓶盖至少 10 个或鼓励瓶盖至少 20 个时可兑换，输出 `1`，否则输出 `0`。

### 思路

两个条件只要有一个成立即可，因此使用 `lucky >= 10 or encouragement >= 20`。再用 `int` 转成题目要求的 `1`、`0`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

“满足任一条件”对应逻辑或 `or`；不要误写成要求同时满足的 `and`。
