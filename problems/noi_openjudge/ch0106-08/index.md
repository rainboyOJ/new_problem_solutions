---
oj: "noi_openjudge"
problem_id: "ch0106-08"
title: "石头剪刀布"
description: "用取模循环访问两人的出拳周期，并按胜负映射累计胜场。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "数组", "循环", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0106/08/
---

[[TOC]]

### 题意

两人按各自周期出石头、剪刀、布，比赛 $N$ 轮后比较谁获胜轮数更多。

### 思路

第 $i$ 轮的出拳下标分别为 `i % a_length` 和 `i % b_length`。字典 `wins_against` 记录每种拳能战胜的拳，比较映射结果即可计数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(N)$，除两个周期外额外空间复杂度为 $O(1)$。

### 总结

周期性序列访问的核心是下标对周期长度取模。
