---
oj: "roj"
problem_id: "1357"
title: "车厢调度(train)"
description: "车站 C 是栈，目标是 1..n 的栈混洗：对每个出站车厢把更小编号的未出站车厢全部入栈，检查栈顶恰好匹配，单遍贪心模拟 O(n) 判定。"
difficulty: "入门"
date: 2026-09-30 06:49
updated: 2026-10-05 11:52
toc: true
tags: ["栈", "模拟", "贪心"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1357
---

[[TOC]]

## 题目描述

$n$ 节车厢按 $1,2,\dots,n$ 顺序从 A 驶入，经车站 C（栈）驶向 B。判断能否以给定顺序 $a_1,\dots,a_n$ 出站。$n \le 1000$。

## 思路

车站 C 是栈。要让 $a_i$ 出站，所有编号 $\le a_i$ 且尚未出站的车厢必须先入栈。维护 `cur`（下一节未入栈车厢）和栈，对每个目标 $a_i$：若 $a_i \ge cur$ 则把 $cur..a_i$ 入栈；然后弹出栈顶，若栈顶不是 $a_i$ 则无解。全部成功输出 `YES`。

## 参考代码

@include-code(./main.cpp, cpp)
