---
oj: "noi_openjudge"
problem_id: "ch0111-04"
title: "网线主管"
description: "以厘米为整数单位二分长度，用可切出的段数判断可行性。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["二分", "贪心", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0111/04/
---

[[TOC]]

### 题意

将库存网线切成至少指定数量的等长段，求能得到的最大长度，结果精确到厘米。

### 思路

把米转换为厘米整数，避免浮点误差。若每段长度为 `length`，一条网线能贡献 `wire // length` 段；总段数不少于需求时该长度可行。长度越短越容易可行，满足二分答案的单调性。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n \log M)$，$M$ 是最长网线的厘米长度；空间复杂度为 $O(n)$。

### 总结

要求固定小数精度时，先转换为最小单位整数常能让二分更可靠。
