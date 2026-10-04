---
oj: "roj"
problem_id: "1201"
title: "菲波那契数列"
description: "按定义预处理 F(1..20)，每个询问 O(1) 回答。"
difficulty: "入门"
date: 2026-09-29 23:16
updated: 2026-10-05 05:26
toc: true
tags: ["入门", "递推", "递归", "记忆化搜索", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1201
---

[[TOC]]

## 题目描述

菲波那契数列的第 1、2 个数都为 1，之后每个数都等于前面 2 个数之和。输入第 1 行是测试数据的组数 $n$，后面 $n$ 行每组一个正整数 $a$（$1\leqslant a\leqslant 20$）；输出 $n$ 行，每行输出菲波那契数列中第 $a$ 个数的大小。

样例输入 `4 5 2 19 1`，样例输出 `5 1 4181 1`（输入输出均为每行一个数）。

## 思路

按定义从 $F(1)=F(2)=1$ 自底向上递推出 $F(3),\dots,F(20)$ 预处理进数组，之后每个询问 $a$ 直接输出 $F(a)$ 即可。$F(20)=6765$ 很小，用 `ll` 存也不存在溢出问题。

## 参考代码

@include-code(./main.cpp, cpp)
