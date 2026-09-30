---
oj: "roj"
problem_id: "1666"
title: "「一本通 6.7 练习 1」取石子游戏"
description: "多堆取石子博弈用 SG 定理拆成独立子游戏：打表每堆 SG 值后异或得整体状态，必胜当且仅当异或和非零，首步选落点使异或归零。"
difficulty: "提高+/省选-"
date: 2026-10-01 01:40
updated: 2026-10-01 01:48
toc: true
tags:
  - "博弈论"
  - "SG 定理"
  - "Nim"
favorite: false
favorite_reason: ""
categories:
  - "博弈论"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1666
---

[[TOC]]

## 形式化题目

$N$ 堆石子，第 $i$ 堆有 $A_i$ 个。两人轮流操作，每次从一堆中取走 $B$ 个石子，$B$ 属于给定集合 $\{B_1, \dots, B_M\}$（递增）。无法操作者输。先手小 H 问是否有必胜策略；若有，输出第一步取哪堆、取多少个。

## 正解

### 思路

#### 1. 每堆是独立子游戏：SG 定理

单堆石子的取法只影响本堆，$N$ 堆构成 $N$ 个独立子游戏的和。由 **Sprague-Grundy 定理**，整体局面的 SG 值是各堆 SG 值的异或：

$$SG(\text{全局}) = SG(A_1) \oplus SG(A_2) \oplus \cdots \oplus SG(A_N)$$

- 全局 SG $= 0$：先手必败（输出 `NO`）；
- 全局 SG $> 0$：先手必胜（输出 `YES`）。

#### 2. 单堆 SG 的递推

$$SG(x) = \mathrm{mex}\{SG(x - B_i) \mid B_i \le x\}$$

`mex` 是集合中最小的未出现非负整数。按 $x$ 从小到大递推打表，$x$ 的上限是 $\max A_i$。

**实现技巧**：求 mex 不用每轮 `set()` 清零，用 `stamp[v] == x` 时间戳标记"值 $v$ 在第 $x$ 轮被占用"，$x$ 复用为时间戳，每轮 O(取法数) 扫描缺失值即可。

#### 3. 构造首步

必胜时找一堆 $i$ 与合法取法 $take$，使取后该堆落点的 SG 满足：

$$SG(A_i - take) = SG(\text{全局}) \oplus SG(A_i)$$

即取后全局异或和恰好为 0，把必败态甩给对手。取法集合递增，枚举 $take \le A_i$ 遇到即输出。

### 代码

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：打表 $O(\max A_i \cdot M)$；求首步 $O(N \cdot M)$。
- **空间复杂度**：$O(\max A_i)$ 存 SG 表。

## 总结

- 多堆取石子的标准模型：SG 定理把全局异或化为单堆 SG 问题，先手必胜 $\iff$ 异或和非零。
- mex 的时间戳技巧省掉每轮清零，把常数压到最低。
- 首步构造即"异或归零"：找一堆把它的 SG 改成 `全局异或 ^ 自己` 的目标值。
