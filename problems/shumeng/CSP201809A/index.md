---
oj: "shumeng"
problem_id: "CSP201809A"
title: "卖菜"
description: "保存第一天价格，按端点两项和中间三项的整数平均值计算第二天价格。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201809A
---

[[TOC]]

### 题意

给出一排店铺第一天的菜价。每家店第二天采用自己与相邻店铺第一天菜价的平均值，端点只有一个邻居，输出全部第二天菜价。

### 思路

可以直接枚举当前店能看到的下标范围 `i-1..i+1`，把存在的价格求和后除以数量。

@include-code(./brute.cpp, cpp)

正式计算把两端单独处理：第一个和最后一个店取两个价格的平均，中间店取三个价格的平均。注意所有新价格都依赖第一天价格，不能在原数组上边算边覆盖。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n)$，保存输入和输出数组的空间复杂度为 $O(n)$。

### 总结

同步更新题的核心是区分旧状态和新状态。端点的参与项只有两项，使用整数除法即可符合题目的去尾规则。
