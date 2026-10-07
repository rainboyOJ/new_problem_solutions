---
oj: "roj"
problem_id: "1229"
title: "电池的寿命"
description: "两节电池同时放电：总电量给出上界 Σ/2，单节速率上限再给出上界 Σ−max，答案取小者，按比例换电即可取到。"
difficulty: "普及-"
date: 2026-09-30 00:46
updated: 2026-10-05 06:05
toc: true
tags: ["贪心", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1229
---

[[TOC]]

## 题目描述

游戏机有两个电池槽，必须同时装有电池才能工作；第 $i$ 节电池能用 $a_i$ 小时（每小时耗 1 格电量），随时可以换下再换回（剩余电量保留）。输入多组数据，每组第一行是电池数 $N$（$2 \leqslant N \leqslant 1000$），第二行是 $N$ 个正整数 $a_i$。对每组数据输出最长连续使用时间，保留 1 位小数。样例：输入 `2` / `3 5` 输出 `3.0`；输入 `3` / `3 3 5` 输出 `5.5`。

## 思路

设总电量 $\Sigma$、最大电量 $M$，答案 $T = \min(\Sigma/2,\ \Sigma - M)$：两槽每小时合计耗 2 格给出 $T \leqslant \Sigma/2$；单节每小时最多耗 1 格、其余电池共 $\Sigma - M$ 格要撑起另一半，给出 $T \leqslant \Sigma - M$。两个上界都能通过"按比例换电"构造取到（$M \leqslant \Sigma/2$ 时所有电池恰在 $\Sigma/2$ 同时耗尽，$M > \Sigma/2$ 时最大电池以速率 1 放电、其余按比例），故取小者即精确答案，只需一次求和与取最大。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
