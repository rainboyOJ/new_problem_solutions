---
oj: "roj"
problem_id: "1286"
title: "怪盗基德的滑翔翼"
description: "把一次单向滑翔拆成两个方向的最长下降子序列：高度取负后就是标准 LIS，用 tails 数组按长度维护最小结尾、二分定位，每个方向 O(N log N)，两方向取较大值即为答案。"
difficulty: "普及-"
date: 2026-09-30 03:26
updated: 2026-10-06 02:35
toc: true
tags: ["动态规划", "最长上升子序列", "二分", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1281"
    reason: "最长上升子序列的标准 DP/二分模板；本题把下降方向取负后，复用的就是同一套计算。"
common:
  - oj: "luogu"
    problem_id: "P1571"
    reason: "同难度同型题（M5 自 pre 移入；master 重新定级后两者同档）：B 的二分 LIS 里 lower_bound_pos 复用的正是 A 教的「在有序序列里找第一个 >= x 的位置」这一步，只是从判断元素存在变成在 tails 上定位替换点，再叠加取负转 LIS 与正反两方向取最大这两个额外流程。"
  - oj: "roj"
    problem_id: "1283"
    reason: "同样对序列正反各做一次 LIS，区别是登山要在峰顶把上升、下降两段拼成一条路线，本题只能取其中一个方向。"
recommend: []
source: https://roj.ac.cn/problem/1286
---

[[TOC]]

## 题目描述

N 幢高度互异的建筑排成一条线，怪盗基德从任意一幢出发，选定一个方向后中途不能改，每一步只能飞向更低的建筑（可跳过中间）。求起点、方向任选时最多能经过的建筑数（含起点，K<100 组，每组 N<100）。样例输入：`3 / 8 / 300 207 155 299 298 170 158 65 / 8 / 65 158 170 298 299 155 207 300 / 10 / 2 1 3 4 5 6 7 8 9 10`，输出：`6 6 9`。

## 思路

方向不能改，左右各算一次后取较大值；高度只能下降，把高度取反就变成标准 LIS——`tails[L]` 记长度为 L 的上升子序列的最小结尾（严格递增），每个值二分定位：能接就追加，否则替换同长度结尾，单点 O(N log N)。

## 参考代码

@include-code(./main.cpp, cpp)