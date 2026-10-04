---
oj: "roj"
problem_id: "1245"
title: "不重复地输出数"
description: "值域是整个 int 范围不能开桶，用 set 去重并自动保持升序，时间 O(n log n)。"
difficulty: "入门"
date: 2026-09-30 01:33
updated: 2026-10-05 06:55
toc: true
tags: ["排序", "去重", "哈希", "入门", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1245
---

[[TOC]]

## 题目描述

输入格式：第一行一个整数 n（$1 \leqslant n \leqslant 100000$），之后一行 n 个用空格分隔的整数，每个数在 int 范围内。输出格式：一行，从小到大不重复地输出这些数，相邻两个数之间用单个空格隔开。保证不同的数不超过 500 个。样例：输入 `5` 与 `2 4 4 5 1`，输出 `1 2 4 5`。

## 思路

数值范围是整个 int，按值域开桶会爆内存，所以按实际出现过的数组织：读入后放入 `set`，插入时自动去重，遍历时自动升序。依次输出 set 中的每个数即可，时间 $O(n \log n)$。

## 参考代码

@include-code(./main.cpp, cpp)
