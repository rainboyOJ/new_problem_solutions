---
oj: "noi_openjudge"
problem_id: "ch0105-22"
title: "津津的储蓄计划"
description: "按月更新现金和整百储蓄，首个现金不足月输出负月份。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "循环", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/22/
---

[[TOC]]

### 题意

每月获得 300 元，按预算消费后存入所有整百金额；若首次现金不足，输出负月份，否则年末储蓄返还 120%。

### 思路

维护手头现金 `cash` 和已存金额 `savings`。每月先加 300 再扣预算，负数立即失败；否则将 `cash // 100 * 100` 存入妈妈处并保留余数。`for...else` 的 `else` 只会在 12 个月没有 `break` 时执行，正好处理年末结算。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

月份固定为 12，时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

状态模拟题按题目时间顺序更新变量；`for...else` 适合区分“中途失败”和“正常完成”。
