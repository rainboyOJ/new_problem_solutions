---
oj: "shumeng"
problem_id: "CSP202605A"
title: 银行家舍入
description: "按字符串读取一位小数，分别实现普通四舍五入和向偶数舍入。"
date: 2026-07-31 16:22
toc: true
tags: ["字符串", "模拟", "浮点数"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202605A
difficulty: "未知"
---

[[TOC]]

### 题意

给出若干个保留一位小数的非负实数，分别输出普通四舍五入和银行家舍入后的整数。

### 思路

按字符串读取并在小数点处分割，避免浮点误差。普通四舍五入在小数位大于等于 `5` 时给整数部分加一；银行家舍入在小数位为 `5` 时只在整数部分为奇数时加一，其余情况与普通规则相同。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设所有整数部分的总长度为 `L`，时间复杂度为 `O(L)`，额外空间复杂度为 `O(n)`。

### 总结

半整数是两种舍入规则唯一不同的地方，直接按题面判断整数部分奇偶性即可。
