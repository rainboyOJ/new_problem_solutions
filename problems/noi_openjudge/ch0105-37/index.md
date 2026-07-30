---
oj: "noi_openjudge"
problem_id: "ch0105-37"
title: "雇佣兵"
description: "逐个战斗期计算补满体力所需能量，并按当前战斗力更新增量。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "数学", "循环", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/37/
---

[[TOC]]

### 题意

雇佣兵每次必须把体力补满 $M$ 才能战斗。每个能量元素至多恢复当前战斗力 $N$ 的体力；战斗 $M$ 天后，战斗力增加 $\lfloor M/N \rfloor$。给定能量元素数，求最终最大战斗力。

### 思路

一次战斗期前至少需要 $\lceil M/N \rceil$ 个能量元素，即 `(M + N - 1) // N`。能量不足时无法开始新的战斗期，循环结束。

若能开始，就扣除这些元素，并按本期开始时的战斗力增加 `M // N`。更新必须在扣除能量后进行，但两个公式都使用本期旧的战斗力。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设能完成的战斗期数为 $t$，时间复杂度为 $O(t)$，额外空间复杂度为 $O(1)$。

### 总结

按“能否开始一个完整周期”模拟时，先计算本期资源需求，再决定是否更新状态。
