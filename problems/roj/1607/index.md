---
oj: "roj"
problem_id: "1607"
title: "「一本通 5.6 例 2」任务安排 2"
description: "分批任务调度的费用 DP 用斜率优化到 O(n)：换记账次序后转移化为单调队列维护下凸壳，用斜率单调的直线切凸壳取最优切点。"
difficulty: "提高+/省选-"
date: 2026-09-30 21:45
updated: 2026-10-07 13:50
toc: true
tags:
  - "动态规划"
  - "斜率优化"
  - "单调队列"
  - "凸壳"
favorite: false
favorite_reason: ""
categories:
  - "动态规划"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1607
---

[[TOC]]

## 形式化题目

$N$ 个任务顺序不变地分成若干**连续批次**执行。每批的执行时间为启动时间 $S$ 加批内各任务耗时 $T_i$ 之和；同批任务同时完成，任务 $i$ 的费用为完成时刻乘费用系数 $C_i$。求总费用最小的分批方案。

## 正解

### 思路

#### 1. 基础 DP

设 $f[i]$ 为前 $i$ 个任务分批的最小总费用，枚举最后一批的起点 $j$（第 $j+1 \dots i$ 个任务为一批）：

$$f[i] = \min_{0 \le j < i} \left\{ f[j] + \left(S + \sum_{t=j+1}^{i} T_t\right) \times \sum_{t=j+1}^{i} C_t \right\}$$

直接枚举是 $O(n^2)$，对 $n = 3 \times 10^5$ 超时。

#### 2. 换记账次序展开转移

记前缀和 $pre_t[i] = \sum_{t \le i} T_t$、$pre_c[i] = \sum_{t \le i} C_i$。一个经典技巧：**提前计算启动时间对后面所有任务的费用贡献**——把 $S$ 视为影响此后全部任务，转移改写为：

$$f[i] = \min_j \left\{ f[j] + (S + pre_t[i] - pre_t[j]) \times (pre_c[i] - pre_c[j]) \right\}$$

展开并把只与 $j$ 有关的量合并（关键的代数变形，使 $i, j$ 解耦为"斜率 × 横坐标 + 截距"）：

$$f[i] = pre_t[i] \times pre_c[i] + \min_j \left\{ y[j] - pre_t[i] \times pre_c[j] \right\}$$

其中 $y[j] = f[j] - pre_t[j] \times (pre_c[i] - pre_c[j]) + S \times (pre_c[i] - pre_c[j])$ 在实现里按等价形式逐项递推计算。

#### 3. 斜率优化 + 单调队列

上式即：用斜率 $k = pre_t[i]$ 的直线去切决策点集 $\{(pre_c[j], y[j])\}$ 的**下凸壳**，取截距最小者。两个单调性使整个过程 $O(n)$：

- **查询斜率单调**：$T_i > 0 \Rightarrow pre_t[i]$ 严格递增，队头最优性一旦被超越就永久失效，`popleft` 弹出；
- **插入横坐标单调**：$C_i > 0 \Rightarrow pre_c[j]$ 严格递增，新点只需在队尾弹出破坏凸性的旧点。

凸性比较用**叉积**（乘法交叉相乘）代替斜率除法，避免浮点误差。每个决策入队出队各一次，总复杂度线性。

### 代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)

### 复杂度

- **时间复杂度**：$O(n)$，每个决策点最多入队、出队各一次，查询与维护均摊 $O(1)$。
- **空间复杂度**：$O(n)$，前缀和数组、DP 数组与单调队列。

## 总结

- 任务安排 2 是斜率优化 DP 的标准模板题：核心是把转移展开整理成「斜率 × 横坐标 + 截距」的直线切凸壳形式。
- 换记账次序（启动费提前摊给后续任务）是让转移可分离的关键变形。
- 查询斜率与插入横坐标双单调 + 叉积判凸，把 $O(n^2)$ 压到 $O(n)$。
