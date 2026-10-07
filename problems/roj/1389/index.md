---
oj: "roj"
problem_id: "1389"
title: "亲戚"
description: "带集合大小的并查集：M 合并时把小家族挂到大家族根下并把人数累加到新根，Q 直接输出 a 的根处 cnt，均摊近似线性。"
difficulty: "普及-"
date: 2026-09-30 08:29
updated: 2026-10-07 13:50
toc: true
tags: ["并查集", "连通块", "等价类", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P1536"
    reason: "B 的 M 操作直接复用 A 教的「合并两个不同代表元时同步维护集合大小」这一步（A 用 size 累加、blocks-=1，B 把计数搬到根上做 cnt[新根]+=cnt[旧根]），只把 A 的输出「blocks-1」换成 Q 查询 cnt[find(a)] 并额外叠加按大小合并与坏行 scanf 语义复刻。"
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

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
