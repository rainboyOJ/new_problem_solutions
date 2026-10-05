---
oj: "roj"
problem_id: "1409"
title: "判决素数个数"
description: "埃氏筛预处理 1~10^5 的素数表，再对闭区间直接求和统计素数个数。"
difficulty: "普及"
date: 2026-09-30 09:12
updated: 2026-10-05 23:10
toc: true
tags: [素数判断, 埃氏筛]
favorite: false
favorite_reason: ""
categories: [数论]
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1409
---

[[TOC]]

## 题目描述

输入两个整数 $X$ 和 $Y$（$1 \le X, Y \le 10^5$），输出两者之间的素数个数（包括 $X$ 和 $Y$）。不保证 $X \le Y$。

**样例输入**
```
1 100
```
**样例输出**
```
25
```

## 思路

值域固定为 $10^5$，用埃氏筛一次性预处理素数表，再把区间 $[\min(X,Y), \max(X,Y)]$ 内的素数个数求和即可。

## 参考代码

@include-code(./main.cpp, cpp)
