---
oj: "roj"
problem_id: "2035"
title: "两只塔姆沃斯牛"
description: "把 John 与牛看成一个联合状态，最多 16000 种，模拟并在状态重现仍未相遇时输出 0。"
difficulty: "普及-"
date: 2026-10-01 04:15
updated: 2026-10-06 09:59
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2035
---

[[TOC]]

## 题目描述

$10 \times 10$ 网格中有障碍物、John（`F`）和两头牛（`C`）。John 与牛初始均朝北，每分钟同时按相同规则移动：前方在界内且无障碍则前进一步，否则原地顺时针转 $90°$。若某分钟末在同一格则追捕结束，输出分钟数；若永远不会相遇，输出 $0$。

## 思路

两人运动完全确定，系统状态为（John 位置/朝向，牛位置/朝向），最多 $400 \times 400 = 16000$ 种。逐分钟模拟，分钟末同格则输出分钟数；若状态重复仍未相遇，说明进入循环，输出 $0$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
