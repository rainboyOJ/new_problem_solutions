---
oj: "roj"
problem_id: "19997"
title: "Color"
description: "把每个红格子的镜像格子也染红，逐格检查一次即可。"
difficulty: "普及-"
date: 2026-08-28 19:52
updated: 2026-10-07 13:50
toc: true
tags: ["哈希", "网格", "思维"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/19997
---

[[TOC]]

## 题目描述

有一个 $n$ 行 $m$ 列的网格，第 $i$ 行第 $j$ 列的格子编号为 $(i-1)\times m + j$（题面原式 $(i-1)\times n+j$ 为笔误）。给定长度为 $a$ 的数列 $s$，依次把对应格子染红。判断染色后的图形是否关于网格竖直中线对称。

## 思路

图形对称等价于每个被染红的格子，其关于竖直中线的镜像格子也必须被染红。用 `map` 存储所有红格编号，对每个编号 $O(1)$ 算出行列并镜像到对称列，再查是否存在。镜像是对合，从红格出发查一遍即可。

## 参考代码

@include-code(./main.cpp, cpp)
