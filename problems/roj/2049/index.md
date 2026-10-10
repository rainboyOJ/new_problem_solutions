---
oj: "roj"
problem_id: "2049"
title: "usaco-3.2.4 饲料调配"
description: "把「配出目标比例」写成 a·F1+b·F2+c·F3=k·T 的整数方程，三种饲料份数都小于 100，于是按份数总和递增枚举 a+b+c，第一组命中即用量最少。"
difficulty: "普及-"
date: 2026-10-01 05:07
updated: 2026-10-07 13:50
toc: true
tags: ["枚举", "数学", "比例", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P2911"
    reason: "B 复用 A 教的「把枚举/扫描顺序定成从小到大的目标键，则首次命中的最优解天然带并列取最小的保证」这一步：A 用从小到大扫描和让次数相同时保留最小和（代码只在 times > best_count 时更新），B 把它改成按 a+b+c 递增枚举、第一组命中直接返回，省去保存候选与比较；B 另叠加的「第一个非零位定倍数 k 再回代校验」判定则是 A 未教的整数倍比例判定。"
common: []
recommend: []
source: https://roj.ac.cn/problem/2049
---

[[TOC]]

## 题目描述

三种混合饲料调配目标饲料：求非负整数份数 $a,b,c$ 与正整数 $k$ 使 $aF_1+bF_2+cF_3=kT$ 且 $a+b+c$ 最小，无解输出 `NONE`（份数均小于 100）。

## 思路

按 $s=a+b+c$ 从 0 到 297 递增枚举、同 $s$ 内按 $a,b$ 递增检查，对每组候选由 $T$ 首个非零位定出倍数 $k$，回代验证 $M=kT$ 且 $k\ge1$，首个命中即最小。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
