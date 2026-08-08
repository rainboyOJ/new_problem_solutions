---
oj: "luogu"
problem_id: "P4715"
title: "【深基16.例1】淘汰赛"
description: "分别找出对阵表左右半区冠军，决赛中能力较低的半区冠军就是亚军。"
difficulty: "入门"
date: 2026-07-16 18:17
toc: true
tags: ["二叉树", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4715
---

[[TOC]]

### 题意

`2^n` 个国家按固定淘汰赛对阵，能力强者必胜。输出亚军编号。

### 思路

决赛一定由对阵表左半区最强者和右半区最强者参加，二者中较强的是冠军，较弱的就是亚军。因此无需逐轮模拟，只需分别取两半最大值，再取能力较小的决赛选手编号。

### Python 知识

- `enumerate(scores,start=1)` 同时得到国家编号和能力值。
- `max(...,key=lambda country:country[1])` 按元组的能力字段选半区冠军。
- `min(finalists,key=...)` 再选较弱的决赛选手。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`key` 函数指定比较依据。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

max/min + key：

@include-code(./main-pythonic.py, python)


### 复杂度

只扫描所有国家一次，时间复杂度 $O(2^n)$，保存选手为 $O(2^n)$。

### 总结

固定单败淘汰赛的亚军一定是决赛败者，而两个决赛选手分别是左右半区最大值。
