---
oj: "roj"
problem_id: "3023"
title: "「Fractal」 分形"
description: "递归构造盒子分形：每个 X 复制到 3×3 块网格的四个角和正中，逐级放大到 3^(n-1) 后按行输出。"
difficulty: "普及"
date: 2026-10-01 10:41
updated: 2026-10-06 11:28
toc: true
tags: ["递归", "分形"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3023
---

[[TOC]]

## 题目描述

$n$ 阶分形：1 阶为 `X`，$n$ 阶由 5 个 $n-1$ 阶分形按十字排列（左上/右上/左下/右下 4 个 + 中上空格），输入多组 $n$（$-1$ 终止），每组输出 $3^{n-1}$ 行图案，组间 `-` 分隔。

## 思路

递归构造：$n$ 阶图案尺寸为 $3^{n-1}$，由 $n-1$ 阶图案复制到四个角落、其余留空，递归到 1 阶填 `X`，直接按行输出即可。

## 参考代码

@include-code(./main.cpp, cpp)
