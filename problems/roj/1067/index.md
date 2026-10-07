---
oj: "roj"
problem_id: "1067"
title: "整数的个数"
description: "值域极小的桶计数：一趟扫描只对 1、5、10 三个目标值各维护一个计数器，非目标值一律忽略。"
difficulty: "入门"
date: 2026-09-29 17:08
updated: 2026-10-05 00:05
toc: true
tags: ["桶计数", "入门"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1067"
---

[[TOC]]

## 题目描述

给定 $k$（$1 < k < 100$）个正整数，每个数都在 $1$ 到 $10$ 之间。统计其中 $1$、$5$、$10$ 各出现的次数。

输入有两行：第一行是正整数 $k$，第二行是用空格分开的 $k$ 个正整数。输出有三行，依次为 $1$、$5$、$10$ 出现的次数。

样例输入：

```
5
1 5 8 10 5
```

样例输出为三行：`1`、`2`、`1`。

## 思路

读入 $k$ 个数，维护计数器 `cnt1`、`cnt5`、`cnt10`，每个数与三个目标值做相等比较，命中就加一，其余值忽略。这是值域极小时的桶计数：扫一遍序列即可，时间 $O(k)$，输出按 $1$、$5$、$10$ 的顺序。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
