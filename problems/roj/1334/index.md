---
oj: "roj"
problem_id: "1334"
title: "【例2-3】围圈报数"
description: "用队列模拟约瑟夫环：未数到 m 的人移到队尾，数到 m 的人出列输出。"
difficulty: "入门"
date: 2026-09-30 05:43
updated: 2026-10-05 10:11
toc: true
tags: ["模拟", "队列", "约瑟夫问题"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1334
---

[[TOC]]

## 题目描述

$n$ 个人围成一圈，编号 $1\sim n$。从第 $1$ 个人开始顺时针报数，数到第 $m$ 的人出列，然后从下一位重新开始报数，直到所有人出列。输出出列顺序。

输入：$n$ 和 $m$。输出：出列顺序。数据范围：$n\leqslant 100$。

## 思路

把当前在圈内的人按顺序放进队列。每次取队头报数，未数到 $m$ 就放回队尾，数到 $m$ 就出列输出，直到队列为空。

## 参考代码

@include-code(./main.cpp, cpp)
