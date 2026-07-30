---
oj: "noi_openjudge"
problem_id: "ch0105-42"
title: "画矩形"
description: "按行判断边界或实心状态，拼接并输出指定字符的矩形。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/42/
---

[[TOC]]

### 题意

按给定高、宽和字符输出矩形。参数为 `1` 时输出实心矩形，为 `0` 时仅保留边界字符，内部用空格填充。

### 思路

逐行输出。首行和末行一定全由绘制字符组成；中间行在实心模式下也全填字符，在空心模式下拼出“左边界 + 中间空格 + 右边界”。

题目保证宽至少为 $5$，所以中间空格数 `width - 2` 始终合法。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

需要输出 $H \times W$ 个字符，时间复杂度为 $O(HW)$，构造单行使用 $O(W)$ 空间。

### 总结

二维图形输出通常先按“边界行、中间行”和“实心、空心”做分类。
