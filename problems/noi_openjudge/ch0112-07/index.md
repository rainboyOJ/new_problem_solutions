---
oj: "noi_openjudge"
problem_id: "ch0112-07"
title: "机器翻译"
description: "用 deque 和 set 模拟 FIFO 内存，统计未命中词典次数。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["队列", "模拟", "集合", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0112/07/
---

[[TOC]]

### 题意

翻译软件的内存按先进先出规则替换，统计读取文章时需要访问外存词典的次数。

### 思路

集合 `memory` 用于 $O(1)$ 判断单词是否已缓存，双端队列 `order` 记录进入先后。未命中时计数；内存满则从队首弹出最早进入的单词，再将新词加入队尾和集合。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

平均时间复杂度为 $O(n)$，空间复杂度为 $O(M)$。

### 总结

FIFO 缓存模拟通常需要“顺序容器 + 成员集合”两份状态。
