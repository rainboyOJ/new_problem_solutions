---
oj: "roj"
problem_id: "3177"
title: "「K-Anonymous Sequence」 K匿名序列"
description: "每个数至少有 k-1 个相同数：排序后连续分段 DP（段长≥k），转移化为直线族取 max 用单调队列维护上凸壳，斜率优化 O(n)。"
difficulty: "省选/NOI-"
date: 2026-10-01 23:20
updated: 2026-10-01 23:43
toc: true
tags:
  - "DP"
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
source: https://roj.ac.cn/problem/3177
---

[[TOC]]

## 形式化题目

非严格递增序列 $a_1\le a_2\le\dots\le a_n$。每次操作可将某个数减 1，求最少操作数使每个数在序列中至少有 $k-1$ 个数与之相同（即每个取值的出现次数 $\ge k$）。

## 正解

### 思路

#### 1. 排序 + 连续分段

只能减不能增，且排序后最优解一定把序列切成若干**连续段**，每段长度 $\ge k$，段内所有数最终取相同值（段内最小值 $a_j$，减到它）。设前缀和 $S$，段 $(j,i]$ 的代价为 $S_i-S_j-(i-j)a_j$。

$$f_i=\min_{j\le i-k}\bigl(f_j+S_i-S_j-(i-j)a_j\bigr),\quad f_0=0$$

#### 2. 斜率优化

整理转移：

$$f_i=S_i-\max_{j}\underbrace{\bigl(i\cdot a_j-c_j\bigr)}_{\text{直线 } y=a_j x-c_j \text{ 在 } x=i},\qquad c_j=f_j-S_j+j a_j$$

- 直线斜率 $a_j$ 随 $j$ 递增（序列非降），查询点 $i$ 也递增；
- 维护**上凸壳**（取 max）：双端队列存决策下标，入队时用叉乘判定弹掉被支配的队尾直线，查询时队头单调后移；
- 同斜率的直线按截距取优，避免凸壳退化。

均摊 $O(1)$ 转移，整体 $O(n)$。

### 代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)

### 复杂度

- **时间复杂度**：$O(n)$（每条直线至多入队出队一次）。
- **空间复杂度**：$O(n)$。

## 总结

- 「相邻同值分组」类问题的标准变形：排序 + 连续段 DP + 段内取最小值的代价公式。
- 转移形如 $f_i=\min_j\{i\cdot k_j+b_j\}$（$k_j$、查询点均单调）时用**单调队列凸壳**斜率优化。
- 叉乘写法避免浮点除法，同斜率直线的支配判定是常见的坑。
