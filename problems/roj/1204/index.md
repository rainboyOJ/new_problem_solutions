---
oj: "roj"
problem_id: "1204"
title: "爬楼梯"
description: "按最后一步跨 1 级还是 2 级分类，得互斥完备的递推 f(n)=f(n-1)+f(n-2)（即斐波那契），预处理 1~30 的表后逐行查表输出。"
difficulty: "入门"
date: 2026-09-29 23:27
updated: 2026-10-05 05:26
toc: true
tags: ["入门", "递推", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1204
---

[[TOC]]

## 题目描述

树老师爬楼梯，每次可以走 1 级或 2 级。输入包含若干行，每行一个正整数 $N$（$1 \le N \le 30$），每行输出走完 $N$ 级的走法数。例如 $N=3$ 时有 $\{1,1,1\},\{1,2\},\{2,1\}$ 共 3 种走法；样例输入为三行 `5`、`8`、`10`，对应输出为 `8`、`34`、`89`。

## 思路

按最后一步跨 1 级还是 2 级分类，两类互斥且完备，得递推 $f(n)=f(n-1)+f(n-2)$，边界 $f(0)=f(1)=1$；先预处理出 $1 \sim 30$ 的答案，再对每行询问直接查表输出。

## 参考代码

@include-code(./main.cpp, cpp)
