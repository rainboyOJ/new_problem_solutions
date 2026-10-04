---
oj: "roj"
problem_id: "1114"
title: "白细胞计数"
description: "线性扫描找出最大、最小值并求和，扣除两端后求平均值，再扫描有效样本找最大绝对偏差。"
difficulty: "入门"
date: 2026-09-29 19:26
updated: 2026-10-05 02:16
toc: true
tags:
  - 模拟
  - 线性扫描
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1114
---

[[TOC]]

## 题目描述

医院采集了 $n$ 份白细胞样本（$2<n\le 300$），去掉一个最大值和一个最小值后，把剩余 $n-2$ 个有效样本的平均值作为分析指标，并输出有效样本与该平均值之差绝对值的最大值。
输入第一行 $n$，随后 $n$ 行每行一个浮点数；输出保留两位小数的平均值和误差，样例输入 `5 12.0 13.0 11.0 9.0 10.0`，输出 `11.00 1.00`。

## 思路

一次扫描求出总和 $S$、最大值 $M$、最小值 $m$，得平均值 $\bar{x}=(S-M-m)/(n-2)$；再扫描一遍，对所有不等于 $M$ 和 $m$ 的样本求 $|a_i-\bar{x}|$ 的最大值，时间复杂度 $O(n)$。

## 参考代码

@include-code(./main.cpp, cpp)
