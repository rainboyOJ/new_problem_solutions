---
oj: "roj"
problem_id: "20009"
title: "吊桥1"
description: "排序后双指针：每趟让最重的史莱姆与最轻的能同乘就配对，趟数即最短时间，O(n log n)。"
difficulty: "入门"
date: 2026-10-02 19:40
updated: 2026-10-06 08:59
toc: true
tags: ["入门", "贪心", "排序", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/20009
---

[[TOC]]

## 题目描述

$n$ 只史莱姆要过一座吊桥，桥的最大载重为 $C$，每次最多同时过 2 只（也可 1 只独过），同一趟上的史莱姆重量和不得超过 $C$；每只过桥时间都是 $1$，求所有史莱姆过完的最短时间。

输入格式：第一行两个数 $n$ 和 $C$；第二行 $n$ 个数，表示每只史莱姆的重量。

输出格式：一个数，最短的过桥时间。

输入样例（$n=5$、$C=10$，重量 $1,2,3,4,5$）：

```
5 10
1 2 3 4 5
```

输出样例：`3`（由输入样例得到）。

数据范围：$1 \leq n \leq 10^5$。

## 思路
每趟耗时恒为 1，最短时间即最少趟数：把重量升序排序后用双指针，最重的一只必须走，若它加上当前最轻的不超过 $C$ 就同乘一趟，否则独占一趟。能配就配不劣于最优（趟数 $=n-$ 配对数），时间复杂度 $O(n \log n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
