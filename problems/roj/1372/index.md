---
oj: "roj"
problem_id: "1372"
title: "小明的账单"
description: "用 multiset 维护未付账单，每天插入新账单后输出并删除最小和最大面额各一张。"
difficulty: "普及-"
date: 2026-09-30 07:30
updated: 2026-10-05 12:23
toc: true
tags: ["模拟", "优先队列", "堆", "懒删除", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1372
---

[[TOC]]

## 题目描述

小明每天收到若干账单。每天需从尚未支付的账单中取出面额最小和最大的两张付清，未付账单累积到下一天。输入天数 $N$ 和每天收到的账单，输出每天支付的两个面额（先小后大）。每天保证至少能支付两张。

## 思路

把未付账单看成一个可重集合，每天只需插入新账单并取删最小、最大两个元素，用 `multiset` 即可在 $O(\log K)$ 内完成每个操作。

## 参考代码

@include-code(./main.cpp, cpp)
