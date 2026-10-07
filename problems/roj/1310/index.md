---
oj: "roj"
problem_id: "1310"
title: "车厢重组"
description: "旋转一次即交换相邻车厢，最少次数恰为逆序对数；离散化后用权值树状数组从左到右先查前缀和、后单点插入，O(n log n) 求出。"
difficulty: "普及-"
date: 2026-09-30 04:17
updated: 2026-10-06 02:35
toc: true
tags: ["树状数组", "离散化", "逆序对", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P1116"
    reason: "B 正解的第一步转化直接沿用 A 教的「相邻交换最少次数=初始逆序对数量」，B 代码里 inversions 即最少旋转次数；区别只在 A 用两层循环 O(n²) 统计，B 把统计换成离散化+权值树状数组 O(n log n)。"
common: []
recommend: []
source: https://roj.ac.cn/problem/1310
---

[[TOC]]

## 题目描述

旧式火车站有一座桥，旋转 180 度可交换相邻两节车厢。给定车厢总数 $n \leq 10000$ 与 $n$ 个互不相同的车厢号，求把车厢按编号升序排好所需的最少旋转次数。

输入：第一行是 $n$，第二行是 $n$ 个车厢号。输出：一个整数表示最少次数。

样例输入：

```
4
4 3 2 1
```

样例输出：

```
6
```

## 思路

每次相邻交换使逆序数变化 $\pm 1$，目标逆序数为 0，故最少次数等于逆序对数。把车厢号离散化到 $1..n$ 后，从左到右用权值树状数组维护"已出现元素"：对当前排名 $r$，先查前缀和得到已出现且不大于它的个数，再用 `已出现总数 − 前缀和` 得到左边比它大的元素数，累加后把当前元素插入。

## 参考代码

@include-code(./main.cpp, cpp)

