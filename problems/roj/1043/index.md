---
oj: "roj"
problem_id: "1043"
title: "整数大小比较"
description: "比较无符号 32 位的 x 与有符号 32 位的 y，把两边统一成 long long 再比，避免 C++ 混合符号比较的隐式转换陷阱。"
difficulty: "入门"
date: 2026-09-29 15:47
updated: 2026-10-04 23:24
toc: true
tags: ["入门", "输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1043
---

[[TOC]]

## 题目描述

输入一行两个整数 `x y`（单个空格隔开），比较大小后输出一个字符：$x > y$ 输出 `>`，$x = y$ 输出 `=`，$x < y$ 输出 `<`。数据范围：$0 \leqslant x < 2^{32}$（无符号 32 位），$-2^{31} \leqslant y < 2^{31}$（有符号 32 位）。

样例：输入 `1000 100`，输出 `>`。

## 思路

本题只有一个比较，考点是无符号/有符号混合比较的类型陷阱：C++ 里 `unsigned` 与 `int` 直接比较时，$y$ 会被隐式转成无符号数（如 $-1$ 变成 $4294967295$）导致方向判反。把 $x$、$y$ 都读成 `long long` 再比较，三种结果直接分支输出即可。

## 参考代码

@include-code(./main.cpp, cpp)
