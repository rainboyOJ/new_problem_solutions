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
difficulty: "未知"
---

[[TOC]]

### 题意

给定 `mu、sigma、n`，标准化后的查表值为 `(n-mu)/sigma`。输出该数在步长 `0.01` 的标准正态分布表中的行、列，下标从 `1` 开始。

### 思路

令 `t=(n-mu)/sigma`。由于 `sigma` 是 `100` 的因子，`t*100` 可以用整数精确计算。设 `hundredths=(n-mu)*100/sigma`，则整数部分的十分位对应行号 `hundredths/10+1`，百分位对应列号 `hundredths%10+1`。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每个查询 `O(1)` 时间、`O(1)` 空间。

### 总结

把小数定位题转换成整数下标运算即可避免浮点误差。
