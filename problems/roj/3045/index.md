---
oj: "roj"
problem_id: "3045"
title: "合并果子"
description: "每次合并两堆果子，代价为重量之和，求最小总代价。用小根堆每次取最小的两堆合并，即 Huffman 树贪心。"
difficulty: "普及"
date: 2026-10-01 11:51
updated: 2026-10-06 11:36
toc: true
tags:
  - 贪心
  - 二叉堆
  - Huffman树
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3045
---

[[TOC]]

## 题目描述

$n$ 堆果子每次选两堆合并（代价为两堆重量和），求合并成一堆的最小总代价（$n \le 10000$）。

## 思路

总代价等于各堆重量乘其合并树深度，重量小的应尽量深，故贪心每次合并当前最轻两堆；用小根堆维护，弹出两个最小值合并后压回并累加代价。

## 参考代码

@include-code(./main.cpp, cpp)
