---
oj: "shumeng"
problem_id: "CSP201312B"
title: "ISBN 号码"
description: "扫描 ISBN 的前九个数字计算带权和，再按模 11 规则校验或替换识别码。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201312B
---

[[TOC]]

### 题意

输入格式正确的 ISBN 字符串 `x-xxx-xxxxx-x`，检查最后的识别码是否等于前九个数字按权重 $1$ 到 $9$ 计算的和模 $11$。余数 $10$ 要写成大写字母 `X`。

正确时输出 `Right`；错误时只替换最后一位，原样输出带连字符的正确 ISBN。

### 思路

先按题面固定位置取出九个数字，直接套用校验公式：

@include-code(./brute.cpp, cpp)

这个做法依赖格式中的固定下标。正式代码更稳妥：从左到右扫描字符串，忽略连字符，只对遇到的前九个数字累加 `数字 × 第几个数字`。最后用余数构造正确识别码，与 `isbn.back()` 比较即可。

注意识别码本身也可能是数字，但它不能参与带权和；因此只在读到前九个数字时累加。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

字符串长度固定为 $13$，时间复杂度和空间复杂度都为 $O(1)$。

### 总结

固定格式模拟题最容易错在“哪些字符参与计算”。把连字符跳过，并明确限制只统计前九个数字，就能避免把最后的识别码重复算入。
