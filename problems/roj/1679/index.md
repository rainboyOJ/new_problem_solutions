---
oj: "roj"
problem_id: "1679"
title: "玉米田"
description: "把每一行的种植状态压成 N 位掩码，筛掉行内水平相邻与贫瘠格后逐行做计数 DP，转移时要求上下两行掩码按位与为 0。"
difficulty: "普及-"
date: 2026-10-01 01:55
updated: 2026-10-06 02:02
toc: true
tags:
  - 动态规划
  - 状态压缩
  - 位运算
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1679
---

[[TOC]]

## 题目描述

$M \times N$ 的玉米田每格为 1（肥沃）或 0（贫瘠），只能在肥沃格种玉米，且相邻（上下左右）两格不能同时种。求种植方案数对 $10^8$ 取模。

## 思路

按行做状态压缩 DP：一行的种植状态用二进制表示，预处理出不含相邻 1 的合法状态及状态对应肥沃格掩码，再枚举相邻两行状态不冲突且都落在肥沃格内的转移，逐行累计方案数即可。

## 参考代码

@include-code(./main.cpp, cpp)
