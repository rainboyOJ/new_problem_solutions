---
oj: "shumeng"
problem_id: "CSP202506A"
title: "正态分布"
description: "把标准化结果放大为百分之一整数，直接拆出正态分布表的行号与列号。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["数学", "模拟"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202506A
---

[[TOC]]

## 形式化题目

给定查询参数 $\mu,\sigma,n$，计算 $Z=\dfrac{n-\mu}{\sigma}$。在步长为 $0.01$ 的正态分布表中，$Z$ 的十分位决定行号、百分位决定列号，行列下标均从 $1$ 开始，输出对应的 $(i,j)$。

## 思路

关键是避免浮点误差，把小数定位转换成整数运算。

### 放大为整数

$\sigma$ 是 $100$ 的因子，所以

$$
\frac{n-\mu}{\sigma} \times 100 = \frac{(n-\mu)\times 100}{\sigma}
$$

可以精确整除，得到整数 `hundredths`，它表示 $Z$ 的百分位数值。

### 拆出行列号

`hundredths / 10` 是十位数（$Z$ 的整数部分与十分位），加 $1$ 得到行号；`hundredths % 10` 是百分位，加 $1$ 得到列号。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

每个查询 $O(1)$ 时间、$O(1)$ 空间。

## 总结

查表定位本质上是按 $0.01$ 的粒度取小数部分。利用 $\sigma \mid 100$ 的性质把除法化为整数乘法，既精确又不需要处理浮点精度问题。