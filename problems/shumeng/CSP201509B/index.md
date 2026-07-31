---
oj: "shumeng"
problem_id: "CSP201509B"
title: "日期计算"
description: "按闰年规则确定二月天数，再依次扣除每月天数定位日期。"
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
source: https://oj.shumeng.tech/p/CSP201509B
---

[[TOC]]

### 题意

给出年份和该年的第几天，输出对应的月份和日期。

### 思路

基准程序从 1 月 1 日逐日推进：

@include-code(./brute.cpp, cpp)

正式做法按月处理。先根据闰年规则确定二月为 28 或 29 天，再不断从 `d` 中减去当前月天数；第一次不能再减时，剩余的 `d` 就是该月日期。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

最多处理 12 个月，时间复杂度为 $O(1)$，空间复杂度为 $O(1)$。

### 总结

日期换算先判断闰年，再把“年内第几天”逐月消耗，能避免手写月份边界公式。
