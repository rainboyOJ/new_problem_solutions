---
oj: "roj"
problem_id: "2029"
title: "usaco-2.2.4 派对灯"
description: "四个按钮只关心奇偶共 16 种组合，按钮作用以 6 为周期，枚举前 6 盏灯的翻转图案并用最少按压次数与 C 同奇偶判定可行性。"
difficulty: "普及"
date: 2026-10-01 03:44
updated: 2026-10-06 09:51
toc: true
tags: ["枚举", "位运算", "周期性"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2029
---

[[TOC]]

## 题目描述

$N$ 盏灯排成一排，初始全部点亮。四个按钮分别翻转：所有灯、奇数号灯、偶数号灯、$3k+1$ 号灯。给定总按压次数 $C$，以及最终必须亮/灭的灯号集合（以 `-1` 结束），求所有满足约束的最终状态（`1` 亮 `0` 灭），按二进制从小到大输出；无解输出 `IMPOSSIBLE`。$10 \le N \le 100$，$0 \le C \le 10000$。

## 思路

同一个按钮按两次等于没按，故只需考虑四个按钮各按 $0/1$ 次的 $2^4=16$ 种奇偶组合。各按钮影响周期分别为 $1,2,2,3$，最小公倍数为 $6$，因此只需算出前 $6$ 盏灯的翻转图案即可平铺到全部 $N$ 盏灯。对每种组合，最少按压次数为 $s$，恰好按 $C$ 次可行的充要条件是 $s \le C$ 且 $C-s$ 为偶数。枚举 $16$ 种图案，保留满足亮灭约束的，排序去重输出。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
