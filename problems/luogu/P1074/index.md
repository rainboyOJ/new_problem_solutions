---
oj: "luogu"
problem_id: "P1074"
title: "[NOIP 2009 提高组] 靶形数独"
description: "位掩码维护行列宫约束，每层选择候选最少空格并回溯最大化加权分数。"
difficulty: "提高+/省选-"
date: 2026-07-16 20:10
toc: true
tags: ["回溯", "MRV", "数独", "位运算", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1074
---

[[TOC]]

### 题意

补全数独，并最大化每格数字乘靶形权重的总和；无解输出 `-1`。

### 思路

行、列、九宫格各用 9 位掩码记录已用数字。候选集合是 `FULL & ~(row | column | block)`。

每层在剩余空格中选择候选数最少的格子（MRV），能最快暴露冲突。通过交换空格列表把选中格放到当前下标，尝试数字后用异或撤销三个掩码；填满时更新最高分。

### Python 知识

- `mask.bit_count()` 直接统计候选数。
- `divmod(position, 9)` 从一维输入位置取得行列。
- 权重可由 `10 - max(abs(r-4), abs(c-4))` 计算，无需硬编码矩阵。
- 数字按 9 到 1 尝试，较早得到高分完整解。

### 代码

@include-code(./main.py, python)

### 复杂度

最坏指数级，MRV 大幅减少实际分支；额外空间 $O(81)$。

### 总结

约束满足问题中，“先处理候选最少变量”通常比固定顺序搜索有效得多。
