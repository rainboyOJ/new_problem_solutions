---
oj: "roj"
problem_id: "1163"
title: "阿克曼(Ackmann)函数"
description: "m≤3、n≤10 的阿克曼函数直接照三分支定义递归求值，最大 A(3,10)=8189 的调用栈 C++ 足够承受。"
difficulty: "入门"
date: 2026-09-29 21:26
updated: 2026-10-05 03:58
toc: true
tags: ["入门", "递归", "递推", "记忆化搜索", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1163
---

[[TOC]]

## 题目描述

阿克曼(Ackmann)函数 $A(m,n)$ 的 $m,n$ 为非负整数（$m \le 3$、$n \le 10$），定义分三条分支：$A(0,n)=n+1$；$m>0,n=0$ 时 $A(m,n)=A(m-1,1)$；$m,n>0$ 时 $A(m,n)=A(m-1,A(m,n-1))$。

输入一行两个整数 $m$ 和 $n$，输出 $A(m,n)$；样例输入 `2 3`，样例输出 `9`。

## 思路

数据规模很小，按题目给出的三条分支逐条翻译成递归函数即可。最大的一组 $A(3,10)=8189$ 需要约 8190 层调用栈，C++ 默认栈深足以承受，所以不必加记忆化，也不必改成递推填表。

## 参考代码

@include-code(./main.cpp, cpp)
