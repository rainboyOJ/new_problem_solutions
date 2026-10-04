---
oj: "roj"
problem_id: "1166"
title: "求f(x,n)"
description: "把嵌套根式看成递推 g_1=sqrt(1+x)、g_k=sqrt(k+g_{k-1})，从内向外一层循环折叠 n-1 次，O(n) 时间 O(1) 空间，保留两位小数输出。"
difficulty: "入门"
date: 2026-09-29 21:39
updated: 2026-10-05 04:06
toc: true
tags: ["递推", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1166
---

[[TOC]]

## 题目描述

求 $n$ 层嵌套根式 $f(x,n) = \sqrt{n + \sqrt{(n-1) + \sqrt{\cdots + 2 + \sqrt{1+x}}}}$，最内层是 $\sqrt{1+x}$。输入一行 `x n`，输出 $f(x,n)$ 保留两位小数。样例：输入 `4.2 10`，输出 `3.68`。

## 思路

令 $g_1=\sqrt{1+x}$，$g_k=\sqrt{k+g_{k-1}}$，答案就是 $g_n$。用一个变量从 $g_1$ 开始，循环 $n-1$ 次执行 `g = sqrt(k + g)`（$k$ 从 2 递增到 $n$），循环方向必须内→外。末尾用 `printf("%.2f")` 完成四舍五入与固定两位补零。

## 参考代码

@include-code(./main.cpp, cpp)
