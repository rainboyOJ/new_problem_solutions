---
oj: "roj"
problem_id: "10026"
title: "Clock"
description: "把 HH:MM:SS 摊成 3×6 位矩阵，按列/按行读出两个 18 位二进制串：时分秒各 6 位二进制占一行，转置拼接即列序串。"
difficulty: "入门"
date: 2026-10-02 19:15
updated: 2026-10-04 14:44
toc: true
tags:
  - "字符串"
  - "模拟"
  - "进制"
favorite: false
favorite_reason: ""
categories:
  - "模拟"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/10026
---

[[TOC]]

## 形式化题目

给定时间 `HH:MM:SS`，把时、分、秒分别写成 **6 位二进制**（补零），依次排成 3×6 的 01 矩阵。输出：

1. **按列读**（每列自上而下，列从左到右）得到的 18 位串；
2. **按行读**（三行首尾相接）得到的 18 位串。

## 正解

### 思路

纯模拟：

- `f"{value:06b}"` 一步得到每行的 6 位二进制；
- 按行串 = 三行拼接；
- 按列串 = 矩阵转置后拼接（`zip(*rows)`）。

时 $\le 23$、分秒 $\le 59$，6 位（可表 0..63）足够。

### 代码

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：$O(1)$。
- **空间复杂度**：$O(1)$。

## 总结

- 矩阵行/列读取用 `zip(*rows)` 转置，是 Python 的一行标准写法。
- 进制格式化 `f"{v:06b}"` 直接补零，避免手写进制转换。
