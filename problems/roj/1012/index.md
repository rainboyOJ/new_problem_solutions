---
oj: "roj"
problem_id: "1012"
title: "计算多项式的值"
description: "读入 x 与系数 a、b、c、d，按 f(x)=ax³+bx²+cx+d 求值并保留 7 位小数输出。"
difficulty: "入门"
date: 2026-09-29 13:20
updated: 2026-10-04 22:31
toc: true
tags: ["入门", "数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1012
---

[[TOC]]

## 题目描述

给定三次多项式 $f(x)=ax^3+bx^2+cx+d$。输入一行 $5$ 个实数：$x,a,b,c,d$（顺序与样例一致），输出 $f(x)$，保留到小数点后 $7$ 位。

输入样例：

```
2.31 1.2 2 2 3
```

输出样例：

```
33.0838692
```

## 思路

直接代入公式：$f(x)=a\cdot x\cdot x\cdot x+b\cdot x\cdot x+c\cdot x+d$，注意第一个数是 $x$ 而不是 $a$；输出用 `fixed` + `setprecision(7)` 同时完成四舍五入与补尾零。

## 参考代码

@include-code(./main.cpp, cpp)
