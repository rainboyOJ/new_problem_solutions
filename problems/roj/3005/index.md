---
oj: "roj"
problem_id: "3005"
title: "费解的开关"
description: "枚举第一行 32 种开关操作，自顶向下由上一行灭灯状态唯一确定下一行操作，结合位运算快速递推与 6 步剪枝。"
difficulty: "普及"
date: 2026-10-01 09:19
updated: 2026-10-06 10:53
toc: true
tags:
  - "递推"
  - "位运算"
  - "状态压缩"
favorite: false
favorite_reason: ""
categories:
  - "算法竞赛进阶指南"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3005
---

[[TOC]]

## 题目描述

$5 \times 5$ 的灯阵，每次选择一个灯，把它和上下左右的灯状态翻转。$1$ 表示亮，$0$ 表示灭。给定 $n$ 个初始局面，求每个局面在不超过 6 次操作内使所有灯变亮的最少步数；无法做到输出 $-1$。

## 思路

枚举第一行的 32 种按法；第一行确定后，上一行未亮的列唯一决定下一行必须按的开关，逐行递推。用 5 位二进制表示一行，位运算完成翻转，过程中累计步数超过 6 就剪枝。

## 参考代码

@include-code(./main.cpp, cpp)
