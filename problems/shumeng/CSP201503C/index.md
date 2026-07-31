---
oj: "shumeng"
problem_id: "CSP201503C"
title: "节日"
description: "顺推每年元旦的星期，利用月初星期和模 7 公式定位第几个指定星期。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "日期"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201503C
---

[[TOC]]

### 题意

对每年求指定月份的第 $b$ 个星期 $c$；不存在时输出 `none`。

### 思路

先看从 1850 年开始逐日模拟的基准程序：

@include-code(./brute.cpp, cpp)

若目标月 1 日是星期 `first`，第一个星期 `c` 的日期为 `1 + (c-first+7)%7`，第 $b$ 个再加 `7*(b-1)`。超过该月天数则不存在。程序顺推每年元旦星期，并根据闰年规则求月长。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设年份数为 $Y$，时间复杂度为 $O(Y)$，空间复杂度为 $O(1)$。

### 总结

日期题先固定星期的编号方式，再用“月初星期 + 模 7 偏移”计算目标日；闰年规则只影响每月天数和下一年元旦的星期。
