---
oj: "roj"
problem_id: "1404"
title: "我家的门牌号"
description: "枚举总家数 m，按 32 位 int 溢出语义模拟 std.cpp 的 i*i+i-2n 判定，使 x=(m(m+1)/2-n)/3 落在 [1,m] 时输出。"
difficulty: "入门"
date: 2026-09-30 09:00
updated: 2026-10-05 23:03
toc: true
tags: ["数论", "枚举", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1404
---

[[TOC]]

## 题目描述

门牌号从 $1$ 到 $m$ 顺序编号。给定 $n$，求满足 $(\frac{m(m+1)}{2}-x)-2x=n$ 的我家门牌号 $x$ 与总家数 $m$（$1\leqslant x\leqslant m$，$n<100000$，解唯一）。输入一个正整数 $n$，输出 `x m`。样例：$n=100$ 时输出 `12 16`。

## 思路

枚举总家数 $m$，则其余家门牌号之和减去我家门牌号两倍等于 $\frac{m(m+1)}{2}-3x=n$，即 $x=\frac{m(m+1)/2-n}{3}$。因官方数据由会 32 位溢出的 `std.cpp` 生成，需用 `int` 语义计算 $m(m+1)-2n$ 并判断其被 $6$ 整除且商为正，从而与答案文件一致。

## 参考代码

@include-code(./main.cpp, cpp)
