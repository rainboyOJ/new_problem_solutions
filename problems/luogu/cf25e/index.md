---
oj: "luogu"
problem_id: "CF25E"
title: "Test"
description: "枚举三个字符串的拼接顺序，用 KMP 求相邻字符串的最大后缀前缀重叠。"
difficulty: "普及+/提高"
date: 2026-07-16 19:57
toc: true
tags: ["KMP", "最短公共超串", "全排列", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/CF25E
---

[[TOC]]

### 题意

求包含给定三个字符串作为子串的最短字符串长度。

### 思路

固定先后顺序后，每次应让左串后缀与右串前缀重叠尽量长。若一串已经包含另一串，合并结果直接取较长者。

否则对 `right + separator + left` 求前缀函数，最后一个值就是 `left` 后缀与 `right` 前缀的最大重叠长度。三个字符串只有 $3!=6$ 种顺序，全部枚举取最短即可。

分隔字节 `\0` 不会出现在小写字符串中，防止 KMP 匹配跨过边界。

### Python 知识

- `itertools.permutations(strings)` 直接生成 6 种排列。
- `right in left` 使用 Python 底层字符串搜索处理包含关系。
- `min(generator)` 不需要保存所有候选超串。
- `bytes` 可以直接拼接并用 `b"\0"` 作为安全分隔符。

### 代码

@include-code(./main.py, python)

### 复杂度

排列数为常数，每次合并线性，总时间 $O(|s_1|+|s_2|+|s_3|)$，辅助空间同阶。

### 总结

三个字符串时，枚举顺序比设计复杂状态更直接；KMP 则把最大重叠从平方比较降为线性。
