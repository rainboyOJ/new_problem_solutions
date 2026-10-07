---
oj: "roj"
problem_id: "3577"
title: "[NOIP2010-普及] 接水问题"
description: "用小根堆维护每个龙头的最早空闲时刻，依次分配 n 名同学，最后取最大结束时刻。"
difficulty: "普及-"
date: 2026-10-02 08:37
updated: 2026-10-06 14:26
toc: true
tags: ["模拟", "贪心", "优先队列", "堆", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3577
---

[[TOC]]

## 题目描述

学校有 $m$ 个龙头，$n$ 名同学按顺序接水，第 $i$ 人需接 $w_i$ 秒。开始第 $1\sim m$ 人各占一个龙头同时接水；某人第 $x$ 秒结束后，队首下一人第 $x+1$ 秒立刻顶上。求所有人接完水需要多少秒。

**输入**：$n\ m$，然后 $n$ 个整数 $w_i$。  
**输出**：一个整数，总时间。  
**数据范围**：$1\le n\le 10000,\ 1\le m\le 100,\ 1\le w_i\le 100$。

## 思路

把每个龙头抽象为「下一次空闲时刻」，用小根堆维护这 $m$ 个时刻。依次处理每名同学：取出堆顶（最早空闲的龙头），占用 $w_i$ 秒后把新的结束时刻压回堆。答案为所有龙头结束时刻的最大值。

## 参考代码

@include-code(./main.cpp, cpp)
