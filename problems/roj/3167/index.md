---
oj: "roj"
problem_id: "3167"
title: "「Substract」 减操作"
description: "把 n-1 次减操作看成符号模型 a1±a2±…±an，线性DP求一组可行符号，再按固定规则还原每次操作的位置。"
difficulty: "普及"
date: 2026-10-01 22:29
updated: 2026-10-06 02:35
toc: true
tags: ["动态规划", "线性DP", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P1877"
    reason: "B 的符号求解直接沿用 A 教的加减双向可达性 DP：把音量下标换成平移后的和值，用同一 f[i][v]=f[i-1][v-a_i]∨f[i-1][v+a_i] 转移判可达，再在 A 没有的最后一步上回溯符号并还原操作位置。"
  - oj: "luogu"
    problem_id: "U663295"
    reason: "B 直接把 A 教的「布尔可达性 dp、由已有可达和加/减一项推出新和」搬到符号模型：main.py 的 f[i][s] 就是 A 的 dp[c]，转移只在 ±a_i 两个方向做同一件事，A 是无价值的纯可行性 01 背包，B 在此之上叠加符号建模与操作位置还原。"
  - oj: "roj"
    problem_id: "1195"
    reason: "B 的可行性线性 DP 直接复用 A 教的「每个 a_i 沿 +a_i/-a_i 两支平移可达集合」这一步（代码里 f[i][j+ai]/f[i][j-ai] 赋符号），在其上再叠加把符号回译为减操作位置的新流程。"
common: []
recommend: []
source: https://roj.ac.cn/problem/3167
---

[[TOC]]

## 题目描述

给定数组 $a_1\sim a_n$ 与目标 $t$。一次减操作把相邻两项 $a_i,a_{i+1}$ 替换为 $a_i-a_{i+1}$，数组长度减一。经过 $n-1$ 次操作后只剩一个数，要求输出每次操作的位置 $p_k$（当前数组中的 1-based 位置），使最终结果等于 $t$；无解则不输出。

输入：$n,t$，随后 $n$ 行各一个 $a_i$。输出：$n-1$ 行，每行一个操作位置。数据范围 $1\le n\le100$，$1\le a_i\le100$，$-10^4\le t\le10^4$。

样例：$n=5,t=4,a=[12,10,4,3,5]$，输出 `2 3 2 1` 为合法方案之一。

## 思路

每次合并 $x-y$ 时，减数所在块的系数整体变号，因此最终结果可写成 $a_1\pm a_2\pm\dots\pm a_n$，$a_1$ 恒正、$a_2$ 恒负。用线性 DP 求一组能凑出 $t$ 的符号，再按固定规则还原操作位置：先依次消去取正号的项，最后从位置 1 连续消去取负号的项。

## 参考代码

@include-code(./main.cpp, cpp)
