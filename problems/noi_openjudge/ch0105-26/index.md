---
oj: "noi_openjudge"
problem_id: "ch0105-26"
title: "统计满足条件的4位数个数"
description: "逐位拆分四位数，判断个位是否大于其余三位之和。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "数位", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/26/
---

[[TOC]]

### 题意

给出 $n$ 个四位数，统计其中个位数字严格大于千位、百位和十位数字之和的数目。

### 思路

把每个数当作四个字符组成的字符串。将四个字符转换为数字后，前三位的和是 `sum(digits[:3])`，最后一位是 `digits[3]`，直接比较即可。

`answer += condition` 利用了 Python 中 `True` 会按整数 `1`、`False` 会按整数 `0` 参与运算，正好完成条件计数。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

每个数只处理四个数位，时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。

### 总结

当题目只关心十进制的各个数位时，字符串下标往往比反复除以 $10$ 更直观。
