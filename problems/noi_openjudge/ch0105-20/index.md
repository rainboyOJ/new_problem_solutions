---
oj: "noi_openjudge"
problem_id: "ch0105-20"
title: "球弹跳高度的计算"
description: "逐次折半累计前十次落地路程，并输出第十次反弹高度。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/20/
---

[[TOC]]

### 题意

球从高度 $h$ 落下，每次反弹到上一高度一半。求第 10 次落地前总路程，以及第 10 次反弹高度。

### 思路

第一次只经过向下的 $h$。之后每次反弹高度既要上升又要下降，因此九个完整往返各加 `2 * height`；第十次落地后再折半一次得到第十次反弹高度。题面样例恰处于有效数字舍入边界，使用 `Decimal` 和半向上舍入匹配其 `%g` 输出。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

循环次数固定为 9，时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

弹跳题要单独处理第一次下降和最后一次反弹，避免把往返次数多算或少算一次。
