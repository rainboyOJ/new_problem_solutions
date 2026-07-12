---
oj: "luogu"
problem_id: "P1022"
title: "[NOIP 2000 普及组] 计算器的改良"
description: "线性扫描方程字符串，分别统计未知数系数和常数和，整理成一元一次方程后直接求解。"
difficulty: "普及-"
date: 2026-06-19 10:31
toc: true
tags: ["字符串", "模拟", "数学"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1022
---

[[TOC]]

### 题意

给出一个合法的一元一次方程，只含整数、一个小写字母未知数、`+`、`-`、`=`。

要求求出这个未知数的值，并保留三位小数输出。

### 思路

这题直接扫描整条方程就行。

最直接的教学版写法如下：

@include-code(./brute.cpp, cpp)

我们把等式左右两边统一移到左边。

扫描每一项时，维护：

- 当前项的正负号 `sign`
- 当前在等号左边还是右边 `side`

然后把解析出的项分成两类累计：

- 未知数项加到 `coef_sum`
- 常数项加到 `const_sum`

最后方程一定变成：

`coef_sum * x + const_sum = 0`

于是：

`x = -const_sum / coef_sum`

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：$O(n)$
- 空间复杂度：$O(1)$

### 总结

这题的关键是把字符串解析和代数移项结合起来：

1. 读懂每一项；
2. 正确处理左右两边符号；
3. 最后统一成 `kx+b=0`。

### 一图流解析

这张图把本题的建模、关键转移、实现检查和训练方法压缩到一页，适合读完正文后复盘。

![一图流解析](./one-page-explainer.png)
