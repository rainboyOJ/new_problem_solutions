---
oj: "shumeng"
problem_id: "CSP202206A"
title: "归一化处理"
description: "先计算平均值和方差，再按标准差对每个数据做平移缩放。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "数学", "浮点数"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202206A
---

[[TOC]]

## 形式化题目

给定 $n$ 个整数 $a_1,a_2,\dots,a_n$，先求平均值

$$\bar a=\frac{1}{n}\sum_{i=1}^{n}a_i$$

和方差

$$D(a)=\frac{1}{n}\sum_{i=1}^{n}(a_i-\bar a)^2,$$

再对每个元素输出

$$f(a_i)=\frac{a_i-\bar a}{\sqrt{D(a)}},$$

使得输出序列的平均值为 $0$、方差为 $1$。题目保证 $D(a)\ge 1$。

## 思路

归一化处理分成三步，全部按数学定义直接计算即可。

### 第一步：求平均值

读入数据时同时累加，最后除以 $n$ 得到平均值 $\bar a$。

### 第二步：求方差和标准差

先按定义累加 $(a_i-\bar a)^2$，再除以 $n$ 得到方差 $D(a)$。标准差就是方差的平方根 $\sqrt{D(a)}$。

### 第三步：逐项归一化输出

每一项都执行平移（减均值）和缩放（除以标准差），输出的就是均值为 $0$、方差为 $1$ 的标准化序列。

注意浮点数使用 `double` 存储，输出保留足够的有效数字位数。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

只做两次线性扫描，时间复杂度为 $O(n)$；只需存储原数据，空间复杂度为 $O(n)$。

## 总结

归一化公式的分子负责消去均值，分母负责把方差缩放为 1。题目保证方差非零，因此无需处理除零的边界情况。