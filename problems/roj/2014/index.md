---
oj: "roj"
problem_id: "2014"
title: "铺放矩形块"
description: "枚举 4 块矩形的全排列与横竖方向，对 6 种基本铺放拓扑用 O(1) 宽高公式算最小包围盒，去重输出所有边长解。"
difficulty: "普及-"
date: 2026-10-01 02:58
updated: 2026-10-06 09:36
toc: true
tags: ["枚举", "模拟", "几何"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2014
---

[[TOC]]

## 题目描述

给定 4 个矩形块，边长范围 1~50。把它们不重叠地放入一个边与矩形块平行的封闭矩形，使面积最小。输出最小面积及所有取到最小面积的边长 `P Q`（`P ≤ Q`），按 `P` 升序。

**样例输入/输出**

```
1 2        40
2 3        4 10
3 4        5 8
4 5
```

## 思路

任意合法铺放都可由 6 种基本方案经旋转、镜像得到。枚举 4 块矩形的排列、每块是否旋转，对 6 种方案用 O(1) 宽高公式算最紧包围盒，取面积最小者去重输出。

## 参考代码

@include-code(./main.cpp, cpp)
