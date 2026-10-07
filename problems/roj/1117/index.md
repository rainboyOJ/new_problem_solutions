---
oj: "roj"
problem_id: "1117"
title: "整数去重"
description: "稳定去重：对每个值只保留首次出现位置；按值开布尔桶 seen，左到右扫描，未登记则保留并写入紧凑前缀 keep，O(n) 完成且天然保序。"
difficulty: "入门"
date: 2026-09-29 19:48
updated: 2026-10-05 02:25
toc: true
tags: ["线性扫描", "桶标记", "Python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1117
---

[[TOC]]

## 题目描述

给定长为 $n$ 的整数序列（$1 \le n \le 20000$，$10 \le a_i \le 5000$），对每个值只保留**首次**出现位置，删除其余位置；输入第一行 $n$、第二行 $n$ 个整数；输出一行、用空格分隔，按原顺序排列。样例：`5 / 10 12 93 12 75` → `10 12 93 75`。

## 思路

值域仅 $5001$，按值当数组下标开布尔桶 `seen`；从左到右扫一遍，未出现过则保留并登记到紧凑前缀 `keep`，已出现过则跳过；时间 $O(n)$、空间 $O(V)$，扫描顺序即输出顺序，天然保序。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)