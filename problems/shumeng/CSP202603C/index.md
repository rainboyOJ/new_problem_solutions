---
oj: "shumeng"
problem_id: "CSP202603C"
title: 进程通信
description: "用按长度排序的空闲区间维护 best-fit 分配器，并记录每个进程接口的循环写入位置。"
date: 2026-07-31 16:22
toc: true
tags: ["模拟", "有序集合", "区间合并", "数据结构"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202603C
difficulty: "未知"
---

[[TOC]]

### 题意

模拟 `new`、`send`、`delete` 三类操作。新队列要分配到长度不小于 `L` 的最短空闲连续区间，删除队列后释放并合并内存区间；发送操作在队列中循环写入对象。

### 思路

用两个有序结构维护空闲区间：`map<左端点,右端点>` 用于按地址查找相邻区间，`set<(长度,左端点)>` 用于找到长度至少为 `L` 且最短、最靠左的区间。分配时从 best-fit 区间左端取出 `L` 个地址，剩余部分重新加入结构。

每个接口只需记录区间左右端点和最近一次写入位置。发送时若还没有写入，写入左端点；否则向右移动，越过右端点后回到左端点。删除时释放区间，并和左右相邻空闲区间合并。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每次 `new` 或 `delete` 进行 `O(log q)` 次有序结构操作，`send` 遍历该进程的接口数；总时间复杂度为 `O((q+n)log q + 总发送接口数)`，空间复杂度为 `O(q)`。

### 总结

best-fit 同时需要“按地址合并”和“按长度选择”，分别维护两种排序键可以让这两个操作都保持对数复杂度。
