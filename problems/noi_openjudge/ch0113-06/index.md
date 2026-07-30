---
oj: "noi_openjudge"
problem_id: "ch0113-06"
title: "循环数"
description: "逐个检查 1 到位数的乘积是否为原数字串的循环移位。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "模拟", "高精度", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0113/06/
---

[[TOC]]

### 题意

判断一个允许前导零的数字串是否为循环数：乘以 1 到位数的每个整数后，结果都应是原串的循环移位。

### 思路

原串的所有循环移位都恰好出现在 `s + s` 中。逐个计算乘积后用 `zfill(length)` 保留应有的前导零，检查其长度和是否为 `s+s` 的子串即可。Python 整数能直接处理本题 60 位数字。

### 代码

## Python代码

@include-code(./main.py, python)

### 复杂度

设位数为 $n$，时间复杂度约为 $O(n^3)$，空间复杂度为 $O(n)$。

### 总结

循环移位判定可转化为“是否出现在自身拼接串中”。
