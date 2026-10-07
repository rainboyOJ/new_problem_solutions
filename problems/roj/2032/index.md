---
oj: "roj"
problem_id: "2032"
title: "和为零"
description: "在 1..N 的数列每两数间插入 +、- 或空格（空格表示拼接），枚举全部 3^(N-1) 种符号方案，按 ASCII 序输出和为 0 的表达式。"
difficulty: "普及-"
date: 2026-10-01 04:00
updated: 2026-10-07 13:50
toc: true
tags: ["搜索", "枚举", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P10839"
    reason: "B 的枚举层直接复用 A 的关键观察——搜索空间是小乘积空间时「完整枚举即正解、不需要优化」，A 的 n 层每层 m 选择枚举模板正好对应 B 在 N-1 个间隙每处 3 种符号的枚举；B 只是在此基础上叠加表达式字符串生成、空格拼接求值与 ASCII 顺序输出。"
  - oj: "luogu"
    problem_id: "P2089"
    reason: "B 直接复用 A 教的 itertools.product 枚举固定候选并利用 product 字典序免排序这一点，只是把每位置候选从 1..3 换成符号 ' '、'+'、'-'，并叠加了拼接求值与筛选步骤"
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
