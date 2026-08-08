---
oj: "luogu"
problem_id: "P1496"
title: "火烧赤壁"
description: "按左端点排序所有半开区间，线性合并相交区间并累加并集长度。"
difficulty: "普及-"
date: 2026-07-16 17:48
toc: true
tags: ["排序", "区间合并", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1496
---

[[TOC]]

### 题意

给出若干左闭右开区间，求它们的并集总长度。

### 思路

把区间按左端点排序，维护当前合并段 `[left, right)`。新区间与它分离时结算旧长度，否则把 `right` 扩展到更远处。半开区间长度正好是 `right - left`。

### Python 知识

- 元组默认按第一项、第二项依次排序，`sorted((l, r) ...)` 不需要额外 `key`。
- 生成器把整数流按两个一组构造成区间，减少中间代码。
- `max(right, end)` 直接表达区间右端扩展。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

### 总结

区间并集的标准模板是“排序后维护一个当前合并段”。
