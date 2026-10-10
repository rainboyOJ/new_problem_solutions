---
oj: "roj"
problem_id: "1239"
title: "统计数字"
description: "用 map 统计每个数字出现次数，按键升序输出。"
difficulty: "入门"
date: 2026-09-30 01:08
updated: 2026-10-05 06:19
toc: true
tags:
  - 哈希表
  - 排序
  - 计数
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1239
---

[[TOC]]

## 题目描述
科研调查得到 $n$ 个自然数（$1 \le n \le 200000$，每数 $\le 1.5 \times 10^9$，不同值不超过 $10000$ 个），统计每个不同值的出现次数并按值从小到大输出。第一行 $n$，接下来 $n$ 行每行一个自然数；输出 $m$ 行，每行「值 次数」。完整样例见 `problem.md`。

## 思路
用 `map<ll,int>` 边读边累加计数，键天然升序，最后顺序遍历输出即可，复杂度 $O(n \log m)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)