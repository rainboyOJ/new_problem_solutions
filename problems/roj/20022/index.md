---
oj: "roj"
problem_id: "20022"
title: "书"
description: "先默认全部不带走，每本书改带走只改变 d_i=a_i-b_i，问题变成从 n 个数里取至多 m 个正数使和最大。"
difficulty: "入门"
date: 2026-08-29 00:08
updated: 2026-10-06 09:14
toc: true
tags: ["贪心", "排序"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20022
---

[[TOC]]

## 题目描述

小 W 要搬家，面前有 $n$ 本书，第 $i$ 本书带走的收益为 $a_i$、不带走的收益为 $b_i$，他最多能带走 $m$ 本书，求最大总收益。

输入：第一行 $n,m$；第二行 $n$ 个整数 $a_i$；第三行 $n$ 个整数 $b_i$。输出一行一个整数表示最大收益。

样例输入 #1：`2 1`，$a=\{5,4\}$，$b=\{3,6\}$，输出 `11`。数据范围：$0\le m\le n\le 5\times10^5$，$|a_i|,|b_i|\le 10^9$。

## 思路

先默认全部不带走，基准为 $\sum b_i$；第 $i$ 本书改为带走只带来边际变化 $d_i=a_i-b_i$。于是只需从正的 $d_i$ 里挑不超过 $m$ 个最大的累加（$d_i\le 0$ 的书不带走，名额不必用满），排序取前 $m$ 大即可，注意总和要用 `long long`。

## 参考代码

@include-code(./main.cpp, cpp)
