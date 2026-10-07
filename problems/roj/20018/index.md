---
oj: "roj"
problem_id: "20018"
title: "旋律压缩"
description: "无限循环播放只是周期重复，先用 c mod L 折回单周期，再把压缩串解析成段并用前缀和定位对应音符。"
difficulty: "普及-"
date: 2026-08-28 22:10
updated: 2026-10-07 10:45
toc: true
tags: ["字符串", "前缀和", "模拟"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20018
---

[[TOC]]

## 题目描述

连续相同音符压缩为「字母+次数」段，如 `a4b1c2d4`。给定压缩串 $s'$ 和整数 $c$，求解压后旋律无限循环播放时第 $c$ 个（从 0 开始）音符。

输入一行 $s'$、一行 $c$，输出对应小写字母。样例：`r2d2` + `8` → `r`；`a4b1c2d10` + `100` → `d`。数据范围 $|s'|\le 2\times10^5$，$c\le10^{12}$。

## 思路

把压缩串解析成音符段并累计单周期长度 $L$；令 $k=c\bmod L$，再用前缀和扫描定位 $k$ 所在段。

## 参考代码

@include-code(./main.cpp, cpp)
