---
oj: "roj"
problem_id: "1206"
title: "放苹果"
description: "把 M 个相同苹果放进 N 个相同盘子（可空），按‘有没有空盘’分类记忆化递推求分法数。"
difficulty: "入门"
date: "2026-09-29 23:26"
updated: "2026-10-05 05:32"
toc: true
tags:
  - 递推
  - 递归
favorite: false
favorite_reason: ""
categories:
  - 递推
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1206
---

[[TOC]]

## 题目描述

把 $M$ 个同样的苹果放进 $N$ 个同样的盘子，允许有的盘子空着。盘子无编号，如 `5 1 1` 与 `1 5 1` 算同一种。给定 $t$ 组 $M, N$（$1 \leqslant M, N \leqslant 10$），每组输出不同分法数 $K$。

## 思路

设 $f(m,n)$ 为 $m$ 个苹果放进 $n$ 个相同盘子（可空）的分法数。按“有没有空盘”分类：有空盘时去掉一个空盘，得 $f(m,n-1)$；无空盘时每盘先减一个，得 $f(m-n,n)$。边界 $f(0,n)=1$，$f(m,0)=0$（$m>0$），并用记忆化把重复子问题只算一次。

## 参考代码

@include-code(./main.cpp, cpp)
