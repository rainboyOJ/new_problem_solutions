---
oj: "roj"
problem_id: "1389"
title: "亲戚"
description: "带集合大小的并查集：M 合并时把小家族挂到大家族根下并把人数累加到新根，Q 直接输出 a 的根处 cnt，均摊近似线性。"
difficulty: "普及-"
date: 2026-09-30 08:29
updated: 2026-10-05 12:30
toc: true
tags: ["并查集", "连通块", "等价类", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1389
---

[[TOC]]

## 题目描述

$n$ 个人（$n \leqslant 100\,000$），编号 $1 \dots n$，初始每人自成一家族。$m$ 条操作：
- `M a b`：$a$ 与 $b$ 是亲戚，合并两个家族；
- `Q a`：输出 $a$ 所在家族的人数。

## 思路

并查集维护每个家族的根，根上记录 `cnt`（家族人数）。合并时按大小合并，小家族挂到大家族根下并累加人数；查询时找到根输出 `cnt`。路径压缩保证均摊近似常数。

## 参考代码

@include-code(./main.cpp, cpp)
