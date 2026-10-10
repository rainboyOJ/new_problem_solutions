---
oj: "roj"
problem_id: "1445"
title: "「一本通 1.3 练习 2」平板涂色"
description: "将矩形贴合拓扑依赖抽象为位掩码先决条件，使用状态压缩记忆化搜索结合同色贪心涂满求最少拿起刷子次数。"
difficulty: "普及"
date: 2026-09-30 10:46
updated: 2026-10-05 23:47
toc: true
tags:
  - "状压 DP"
  - "记忆化搜索"
  - "拓扑排序"
favorite: false
favorite_reason: ""
categories:
  - "一本通"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1445
---

[[TOC]]

## 题目描述

平面上有 $N$ 个互不覆盖的矩形，每个矩形由左上角 $(y_1,x_1)$、右下角 $(y_2,x_2)$ 坐标和颜色 $c$ 描述。涂色时必须等所有**紧靠上方**的矩形涂完后才能涂该矩形（$u$ 的下底边与 $v$ 的上顶边共线且水平投影重叠）。每次拿起某种颜色的刷子，可以把当前所有可涂且颜色相同的矩形一次涂满；放下后再拿需重新计数。求涂完所有矩形的最少拿起刷子次数。

## 思路

$N<16$，用二进制掩码 $mask$ 记录已涂矩形。预处理每个矩形的紧靠上方矩形掩码 `pre_mask`。记忆化搜索 `dfs(mask, cur_color)`：若当前颜色还有可涂矩形，贪心全部涂完（不增加次数）；否则枚举所有可涂矩形的颜色换刷，代价 $+1$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
