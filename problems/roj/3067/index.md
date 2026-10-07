---
oj: "roj"
problem_id: "3067"
title: "矩阵距离"
description: "把 01 矩阵中所有 1 作为 BFS 源点，多源同时扩展，每个格子第一次被访问到的层数就是到最近 1 的曼哈顿距离。"
difficulty: "普及"
date: 2026-10-01 13:42
updated: 2026-10-07 12:15
toc: true
tags: ["BFS", "搜索", "多源BFS"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
common: []
recommend: []
source: https://roj.ac.cn/problem/3067
---

[[TOC]]

## 题目描述

给定 $N \times M$ 的 01 矩阵，输出每个格子到最近的 1 的曼哈顿距离（$1 \le N,M \le 1000$）。

## 思路

所有 1 同时作为源点开始多源 BFS 逐层向四邻扩散，某格子首次被扩散到的层数即为到最近 1 的距离；每格最多入队一次，$O(NM)$。

## 参考代码

@include-code(./main.cpp, cpp)
