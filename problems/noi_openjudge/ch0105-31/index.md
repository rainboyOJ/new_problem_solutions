---
oj: "noi_openjudge"
problem_id: "ch0105-31"
title: "开关灯"
description: "从全关状态模拟编号 2 至 M 的倍数灯切换，收集仍关闭的灯。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["模拟", "数组", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0105/31/
---

[[TOC]]

### 题意

有 $N$ 盏灯。1 号人先把所有灯关闭；第 $i$ 号人把编号为 $i$ 的倍数的灯切换状态。操作到第 $M$ 人后，按升序输出仍关闭的灯号，灯号之间用逗号隔开。

### 思路

1 号人操作后，所有灯都处于关闭状态。用布尔数组记录每盏灯是否已被后续操作切换为打开；对每个 `person`，枚举 `person, 2 * person, ...` 并翻转对应状态。

最后按编号扫描数组，保留状态为关闭的灯号，再用 `",".join(...)` 一次性处理逗号格式。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

第 $i$ 个人操作约 $N/i$ 盏灯，总时间复杂度为 $O(N \log M)$，数组空间复杂度为 $O(N)$。

### 总结

“处理某个编号的所有倍数”可直接使用步长为该编号的 `range`，代码与题意一一对应。
