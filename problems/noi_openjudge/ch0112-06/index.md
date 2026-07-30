---
oj: "noi_openjudge"
problem_id: "ch0112-06"
title: "寻宝"
description: "记录每层楼梯位置，用循环下标直接定位第 x 个可上楼房间。"
difficulty: "普及+/提高"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "二分", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0112/06/
---

[[TOC]]

### 题意

从底层给定房间出发，每层按门牌数字选择循环方向上的第 $x$ 个有楼梯房间，并累加每层进入房间的门牌数。

### 思路

每层预处理所有楼梯房间编号。`bisect_left` 找到从当前房间开始遇到的第一个楼梯，其在楼梯列表中的位置加上 `x - 1` 再对楼梯数取模，就是目标房间。这样无需逐个数到 $x$，适合门牌数字很大的情况。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

预处理时间和空间为 $O(NM)$，每层定位为 $O(\log M)$。

### 总结

循环选择第 $x$ 个元素时，转化为下标加法和取模可避免线性模拟。
