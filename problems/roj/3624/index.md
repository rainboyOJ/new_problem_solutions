---
oj: "roj"
problem_id: "3624"
title: "[noip2015-普及] 金币"
description: "把逐天累加改为按段累加：第 N 段共 N 天、每天 N 枚，末段用 min 截断，O(√K) 求前 K 天金币总数。"
difficulty: "普及"
date: 2026-10-02 11:07
updated: 2026-10-06 15:25
toc: true
tags: ["python", "模拟", "数学"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3624
---

[[TOC]]

## 题目描述
国王把金币作为工资发给骑士：第一天收到 $1$ 枚金币；之后连续 $2$ 天每天收到 $2$ 枚；再之后连续 $3$ 天每天收到 $3$ 枚……当连续 $N$ 天每天收到 $N$ 枚金币后，接着连续 $N+1$ 天每天收到 $N+1$ 枚。请计算前 $K$ 天里骑士一共获得多少金币。
**输入格式：** 一个正整数 $K$，表示发放金币的天数（$1 \le K \le 10{,}000$）。
**输出格式：** 一个正整数，即骑士收到的金币总数。
样例 1：输入 `6`，输出 `14`（$1+2+2+3+3+3$）；样例 2：输入 `1000`，输出 `29820`。

## 思路
工资按“段”变化：第 $N$ 段是连续 $N$ 天、每天 $N$ 枚金币，所以段内 $N$ 天累加等价于一次加上 $N \times N$。用 `left` 记录还没算的天数，每轮取 `days = min(wage, left)` 天、累加 `days * wage` 并扣减 `left`，`left` 为 0 即结束——末段不够一整段时被自动截断。

## 参考代码

@include-code(./main.cpp, cpp)
