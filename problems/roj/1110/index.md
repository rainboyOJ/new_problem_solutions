---
oj: "roj"
problem_id: "1110"
title: "查找特定的值"
description: "无序序列线性扫描，找到目标值第一次出现的位置并输出下标，未找到输出 -1。"
difficulty: "入门"
date: 2026-09-29 19:14
updated: 2026-09-29 19:15
toc: true
tags: ["线性查找", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1110
---

[[TOC]]

## 形式化题目

给定一个长度为 n 的整数序列 $a_1, a_2, \dots, a_n$ 和一个整数 x。要求找到最小的下标 i（$1 \leqslant i \leqslant n$）使得 $a_i = x$，输出该下标；若不存在这样的 i，输出 -1。

## 正解

### 思路

序列未排序，无法使用二分查找，只能顺序扫描。从左到右逐个比较 $a_i$ 与 x：

- 若遇到第一个满足 $a_i = x$ 的位置，立即输出 i（题目要求“第一次出现”）。
- 若扫描完整序列都没有匹配，则输出 -1。

下标从 1 开始计数，扫描时注意枚举起点。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n)$，最多遍历 n 个元素。
- 空间复杂度：$O(n)$ 存储输入序列，额外 $O(1)$。

## 总结

本题是无序序列的线性查找模板：从左到右扫描，首次匹配即答案。核心注意点是“下标从 1 开始”以及“第一次出现后立刻停止”。
