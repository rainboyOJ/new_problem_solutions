---
oj: "noi_openjudge"
problem_id: "ch0108-15"
title: "细菌的繁殖与扩散"
description: "每天从旧培养皿向新培养皿分配细菌，中心格得两份且八邻格各得一份。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/15/
---

[[TOC]]

### 题意

九宫格培养皿中心初始有 $m$ 个细菌，每天每个细菌在原格留下两个后代、向八邻格各扩散一个，输出 $n$ 天后分布。

### 思路

每一天新建全零的 `following`，遍历旧矩阵，将当前格数量的两倍加回原格、同样数量加到八个邻格。全部旧格处理完后再替换状态。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

培养皿固定为 $9\times9$、天数至多 $4$，时间和空间复杂度均为 $O(1)$。

### 总结

扩散模拟必须以旧状态生成新状态，避免同一天内重复扩散。
