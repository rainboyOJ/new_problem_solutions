---
oj: "roj"
problem_id: "1351"
title: "【例4-12】家谱树"
description: "把父亲→儿子的辈分关系建为 DAG 的有向边，用 Kahn 拓扑排序输出一个合法辈分序列。"
difficulty: "入门"
date: 2026-09-30 06:34
updated: 2026-10-05 11:23
toc: true
tags: ["拓扑排序", "图论", "DAG"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1351
---

[[TOC]]

## 题目描述

给出每个人（编号 1~N）的儿子列表，每行以 0 结束。要求输出一个序列，使每个人的所有后辈都比他本人后出现；多解时任意输出一个。

## 思路

把“父亲→儿子”的辈分关系建为 DAG 的有向边，对 DAG 做 Kahn 拓扑排序：每次输出入度为 0 的节点，并将其儿子的入度减 1。

## 参考代码

@include-code(./main.cpp, cpp)
