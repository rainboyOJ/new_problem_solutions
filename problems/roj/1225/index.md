---
oj: "roj"
problem_id: "1225"
title: "金银岛"
description: "部分背包模板：按单位重量价值降序贪心，能装全装、装不下就切一部分。"
difficulty: "普及-"
date: 2026-09-30 00:28
updated: 2026-10-05 05:57
toc: true
tags: ["贪心", "排序"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1225
---

[[TOC]]

## 题目描述

口袋承重上限为 $w$，有 $s$ 种金属，第 $i$ 种总重量为 $n_i$，总价值为 $v_i$。金属可任意分割，且价值与重量成正比。求一次能带走的最大价值。输出保留两位小数。

输入：先给测试组数 $k$；每组给出 $w$、$s$，以及 $2s$ 个数 $n_1,v_1,\dots,n_s,v_s$。$1\leqslant w,n_i\leqslant 10000$，$1\leqslant s\leqslant 100$。

## 思路

每种金属单位重量价值为 $v_i/n_i$，是一个常数。按单价从高到低排序后，能装多少就装多少，装不下就切一部分，贪心即可。

## 参考代码

@include-code(./main.cpp, cpp)
