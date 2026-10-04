---
oj: "roj"
problem_id: "1038"
title: "苹果和虫子"
description: "虫子啃过的苹果数是 ⌈y/x⌉（正在啃的那个也不完整），用 (y + x - 1) / x 向上取整一次算出，答案 max(n - ⌈y/x⌉, 0)。"
difficulty: "入门"
date: 2026-09-29 15:24
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
source: https://roj.ac.cn/problem/1038
---

[[TOC]]

## 题目描述

一箱 $n$ 个苹果混进一条虫子，它每 $x$ 小时吃掉一个，吃完一个才啃下一个；经过 $y$ 小时后还剩几个完整的苹果（被啃过一口的都不算完整）？
输入一行三个整数 $n, x, y$，输出剩余个数。样例：输入 `10 4 9`，输出 `7`。

## 思路

虫子啃过的苹果数为 $\lceil y/x \rceil$：9 小时里啃完 2 个、正在啃第 3 个，这 3 个都不完整。用 `(y + x - 1) / x` 一次求出向上取整，答案取 $\max(n - \lceil y/x \rceil,\ 0)$（吃穿整箱时归零）。

## 参考代码

@include-code(./main.cpp, cpp)
