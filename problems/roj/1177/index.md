---
oj: "roj"
problem_id: "1177"
title: "奇数单增序列"
description: "遍历序列，用位运算筛出奇数，升序排序后以逗号分隔输出。"
difficulty: "入门"
date: 2026-09-29 22:16
updated: 2026-10-05 04:25
toc: true
tags: ["入门", "数组", "排序"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1177
---

[[TOC]]

## 题目描述

给定一个长度为 $N$（$N \leqslant 500$）的正整数序列，将其中的所有奇数取出，按升序输出。数据保证至少有一个奇数。

输入格式：第一行为 $N$；第二行为 $N$ 个正整数。输出格式：增序输出的奇数序列，数据之间以逗号间隔。

样例输入：

```
10
1 3 2 6 5 4 9 8 7 10
```

样例输出：

```
1,3,5,7,9
```

## 思路

遍历序列，用 `x & 1` 判奇偶并保留奇数，再对保留的数升序排序，最后以逗号分隔输出即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
