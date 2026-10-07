---
oj: "roj"
problem_id: "3554"
title: "守望者的逃离"
description: "纯跑步与\"够魔就闪、否则休息\"两条路线每秒取较优者，逐秒模拟即可得到最短逃离时间。"
difficulty: "普及"
date: 2026-10-02 07:11
updated: 2026-10-06 13:42
toc: true
tags: ["贪心", "数学", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3554
---

[[TOC]]

## 题目描述

守望者每秒只能做一件事：跑步前进 $17$ 米、休息使魔法值 $+4$、或闪烁前进 $60$ 米并消耗 $10$ 点魔法（魔法不足 $10$ 时不能闪烁）。给定初始魔法 $M$、出口距离 $S$、岛沉没时间 $T$，若能前进至少 $S$ 米则输出 `Yes` 和最短逃离秒数，否则输出 `No` 和 $T$ 秒内能走的最远距离。输入一行三个非负整数 $M,S,T$（$1\le T\le 3\times10^5$，$0\le M\le 1000$，$1\le S\le 10^8$），输出两行如上述。样例：`39 200 4` 输出 `No`、`197`；`36 255 10` 输出 `Yes`、`6`。

## 思路

同时维护两条路线的累计距离：一直跑步的距离，和"魔法够就闪烁、不够就休息"的距离，每秒取较大者作为当前位置。若最优距离达到 $S$，当前秒数就是最短逃离时间；扫完 $T$ 秒仍未达到，输出最终的最优距离。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
