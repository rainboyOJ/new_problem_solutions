---
oj: "roj"
problem_id: "1053"
title: "最大数输出"
description: "读入一行三个整数，用 max 链式调用直接输出三者最大值，负数与相等无需特判。"
difficulty: "入门"
date: 2026-09-29 16:21
updated: 2026-10-04 23:37
toc: true
tags: ["入门", "条件判断", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1053
---

[[TOC]]

## 题目描述

输入一行三个整数（数与数之间一个空格，可能为负），输出三者中的最大值。

样例输入：

```
10 20 56
```

样例输出：

```
56
```

## 思路

读入三个整数，用 `max` 链式调用一次比较取三者最大值即可，负数与相等无需特判。

## 参考代码

@include-code(./main.cpp, cpp)