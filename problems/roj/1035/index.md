---
oj: "roj"
problem_id: "1035"
title: "等差数列末项计算"
description: "前两项唯一确定公差 d=a2-a1，通项公式 a_n=a1+(n-1)·d 一行 O(1) 求末项。"
difficulty: "入门"
date: 2026-09-29 15:41
updated: 2026-10-04 23:06
toc: true
tags: ["入门", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1035
---

[[TOC]]

## 题目描述

给出一个等差数列的前两项 $a_1$、$a_2$，求第 $n$ 项是多少。

输入一行，包含三个整数 $a_1, a_2, n$（$-100 \leqslant a_1, a_2 \leqslant 100$，$0 < n \leqslant 1000$）。输出一个整数，即第 $n$ 项的值。

样例输入：

```
1 4 100
```

样例输出：

```
298
```

## 思路

前两项唯一确定公差 $d = a_2 - a_1$，由等差数列通项公式直接得 $a_n = a_1 + (n-1)\,d$，一次减法、一次乘法、一次加法即可，$O(1)$。公差为负、为零以及 $n=1$ 都被同一公式自然覆盖，无需特判；真实数据可能超出题面声称的 $|a_1|,|a_2| \leqslant 100$，用 `long long` 兜底更稳。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
