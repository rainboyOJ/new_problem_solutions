---
oj: "roj"
problem_id: "1401"
title: "机器翻译"
description: "FIFO 缓存模拟：按顺序处理单词，命中直接翻译，未命中查词典一次并淘汰最早进入的单词。"
difficulty: "普及-"
date: 2026-09-30 08:46
updated: 2026-10-05 12:53
toc: true
tags: ["模拟", "队列", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1401
---

[[TOC]]

## 题目描述

内存容量 $M$，文章长度 $N$。依次处理每个单词：内存中有则直接翻译；没有则查一次词典并放入内存，若内存已满则淘汰最早进入的单词。求查词典次数。单词为非负整数（≤1000）。

## 思路

用数组模拟 FIFO 队列，再用一个标记数组 `inq[1005]` 做 $O(1)$ 命中判断。未命中时计数 +1，满则队首出队，新单词入队尾。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
