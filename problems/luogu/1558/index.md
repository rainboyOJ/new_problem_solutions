---
oj: "luogu"
problem_id: "P1558"
title: "色板游戏"
description: "用最多 30 位的整数位掩码表示颜色集合，线段树支持区间赋色和颜色种类查询。"
difficulty: "普及+/提高"
date: 2026-07-16 23:59
toc: true
tags: ["线段树", "位运算", "区间赋值", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1558
---

[[TOC]]

### 题意

色板初始全为颜色 1，支持区间涂成一种颜色，以及查询区间内出现了多少种颜色。

### 思路

颜色 `c` 用整数 `1 << (c-1)` 表示，节点保存区间颜色集合，合并就是按位或。区间涂色是赋值懒标记；查询得到集合后用 `bit_count()` 统计置位数。

### Python 知识

- Python 整数位数不限，30 种颜色可自然使用一个位掩码。
- `mask.bit_count()` 比手写循环统计二进制位更清楚。
- 字节输入直接比较 `b'C'`、`b'P'`，避免无必要的字符串解码。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

每次涂色或查询 `O(log L)`，空间 `O(L)`。

### 总结

当集合大小不超过机器字长时，位掩码能把集合并、交和计数压缩成整数运算。
