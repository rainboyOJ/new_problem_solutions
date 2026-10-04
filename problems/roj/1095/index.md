---
oj: "roj"
problem_id: "1095"
title: "数1的个数"
description: "枚举 1 到 n，用字符串 count 直接统计每个整数中数字 \"1\" 的个数并求和。"
difficulty: "入门"
date: 2026-09-29 18:29
updated: 2026-10-04 09:30
toc: true
tags: ["枚举", "字符串", "一本通"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1095
---

[[TOC]]

## 形式化题目

给定正整数 $n$（$1 \leqslant n \leqslant 10^4$）。设 $f(i)$ 表示整数 $i$ 的十进制表示中数字 "1" 出现的次数，要求计算

$$\sum_{i=1}^{n} f(i)$$

## 正解

### 思路

由于 $n \leqslant 10^4$，数字总个数很少，每个数最多只有 $5$ 位，因此直接枚举 $1$ 到 $n$ 的每个整数，逐个统计其中 "1" 的个数并求和即可。

以 $n = 12$ 为例：

| 整数 | 十进制 | "1" 的个数 |
| --- | --- | --- |
| 1 | 1 | 1 |
| 2 | 2 | 0 |
| 3 | 3 | 0 |
| 4 | 4 | 0 |
| 5 | 5 | 0 |
| 6 | 6 | 0 |
| 7 | 7 | 0 |
| 8 | 8 | 0 |
| 9 | 9 | 0 |
| 10 | 10 | 1 |
| 11 | 11 | 2 |
| 12 | 12 | 1 |

合计 $5$ 个 "1"，与样例输出一致。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n \cdot d)$，其中 $d$ 为 $n$ 的十进制位数（本题 $d \leqslant 5$）；空间复杂度 $O(1)$。

## 总结

本题数据范围极小，无需复杂优化。利用 Python 的字符串 `count` 和生成器推导，可以把枚举与统计压缩成一行表达式，直接得到答案。
