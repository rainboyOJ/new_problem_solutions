---
oj: "roj"
problem_id: "1052"
title: "计算邮资"
description: "按重量分段计费：1000克内基本费8元，超重部分每500克向上取整加收4元，加急再加5元。"
difficulty: "入门"
date: 2026-09-29 16:21
updated: 2026-10-04 13:05
toc: true
tags:
  - 模拟
  - 分段计费
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1052
---

[[TOC]]

## 形式化题目

给定邮件重量 `w`（克）和一个加急标志 `c`（`y` 或 `n`）。邮资规则如下：

- 若 `w \leqslant 1000`，基础费用为 8 元。
- 若 `w > 1000`，超出部分每 500 克加收 4 元，不足 500 克按 500 克计算。
- 若 `c = y`，额外再加 5 元。

要求输出最终邮资。

## 正解

### 思路

这是一道直接按规则计算的分段计费题，没有循环、搜索或动态规划。

设超重部分为 `e = \max(w - 1000, 0)`。题面要求“不足 500 克按 500 克计算”，即对 `e` 按 500 克向上取整。由于输入为整数，可用整数运算代替浮点 `ceil`：

$$
\text{extra\_units} = \left\lceil \frac{e}{500} \right\rceil = \frac{e + 499}{500}
$$

总邮资即为：

$$
\text{postage} = 8 + \text{extra\_units} \times 4 + \begin{cases} 5, & c = y \\ 0, & c = n \end{cases}
$$

例如样例 `1200 y`：超重 200 克，向上取整为 1 个 500 克单元，超重费 4 元，加急费 5 元，合计 `8 + 4 + 5 = 17`。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(1)$，空间复杂度 $O(1)$。

## 总结

本题的关键是把“不足 500 克按 500 克计算”转化为整数向上取整，避免使用浮点数。实现上将计费规则封装成函数，主流程只负责输入输出。
