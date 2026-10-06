---
oj: "roj"
problem_id: "8013"
title: "记账"
description: "每行 A B 即 v_A += 1、v_B -= 1，三个桶逐行累加净欠账，最后按 D G Z 输出，O(n) 时间 O(1) 额外空间。"
difficulty: "入门"
date: 2026-10-02 16:34
updated: 2026-10-06 16:51
toc: true
tags: ["入门", "桶", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/8013
---

[[TOC]]

## 题目描述

输入 $n$ 行，每行两个字母 $A\ B$（只含 `D`、`G`、`Z`），表示 $A$ 欠 $B$ 一顿饭。输出三行，按 `D G Z` 顺序给出每个人的净额：正数表示欠别人几顿，0 表示不欠不被欠，负数表示借给别人几顿。$0<n\le 10000$。

## 思路

用三个桶记录每个人的净额：每读一行 `A B`，就执行 `v[A] += 1`、`v[B] -= 1`，全部读完后按 `D G Z` 顺序输出三桶即可。

## 参考代码

@include-code(./main.cpp, cpp)
