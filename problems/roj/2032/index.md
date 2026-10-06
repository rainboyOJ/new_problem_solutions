---
oj: "roj"
problem_id: "2032"
title: "和为零"
description: "在 1..N 的数列每两数间插入 +、- 或空格（空格表示拼接），枚举全部 3^(N-1) 种符号方案，按 ASCII 序输出和为 0 的表达式。"
difficulty: "普及-"
date: 2026-10-01 04:00
updated: 2026-10-06 09:51
toc: true
tags: ["搜索", "枚举", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2032
---

[[TOC]]

## 题目描述

给定 $N$（$3 \le N \le 9$），在递增数列 $1, 2, \ldots, N$ 的每相邻两数之间插入 `+`、`-` 或空格，空格表示把这两个数字拼接成一个多位数，再对整个表达式求和。

输入一行一个整数 $N$；按 ASCII 码顺序输出所有和为 $0$ 的表达式，每行一个，空格要原样保留。样例 $N=7$ 的第一条解为 `1+2-3+4-5-6+7`，最后一条为 `1-2-3-4-5+6+7`。

## 思路

每相邻两数间只有 3 种填法，共 $3^{N-1} \le 6561$ 种方案，全部枚举即可。让靠后的空隙变化更快、并按 `' ' < '+' < '-'` 的顺序枚举，产出的表达式天然就是 ASCII 序；求值时按 `+`/`-` 切项、项内去掉空格再拼成整数累加。

## 参考代码

@include-code(./main.cpp, cpp)
