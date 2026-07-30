---
oj: "noi_openjudge"
problem_id: "ch0107-34"
title: "回文子串"
description: "按长度和起点枚举子串，用动态规划递推判断并按要求输出全部回文子串。"
difficulty: "普及/提高-"
date: 2026-07-30 23:01
toc: true
tags: ["动态规划", "字符串", "回文", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/34/
---

[[TOC]]

### 题意

输出所有长度至少为 $2$ 的回文子串，先按长度升序，再按起点升序。

### 思路

设 `is_palindrome[left][right]` 表示该闭区间是否回文。若两端字符相同，且中间区间也是回文，则当前区间回文；单字符对角线先设为真。外层按子串长度枚举、内层按起点枚举，天然满足输出顺序。

#### DP 状态示意

下表展示 `abba` 的关键状态，单元格表示对应子串是否回文：

| 子串 | `bb` | `abba` |
| --- | --- | --- |
| 两端字符相同 | 是 | 是 |
| 内部区间回文 | 单字符 | `bb` |
| 结果 | 是 | 是 |

先确认短区间，再扩展到更长区间，这正是状态依赖方向。

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

状态数为 $O(n^2)$，时间和空间复杂度均为 $O(n^2)$，不含输出本身。

### 总结

回文区间的两端相等与内部回文构成了标准区间 DP 递推。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

<!-- 原解析未提供复杂度说明时，后续人工补充。 -->

### 总结

<!-- 保留原解析内容，不额外编造结论。 -->
