---
oj: "shumeng"
problem_id: "CSP202206B"
title: "寻宝！大冒险！"
description: "枚举树作为左下角，检查平移后的藏宝图 1 集合与窗口内树集合完全相同。"
difficulty: "普及-"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "集合", "网格"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202206B
---

[[TOC]]

### 题意

给出稀疏的绿化图和完整的藏宝图，统计有多少个左下角坐标能使两张图完全重合。藏宝图左下角一定是树。

### 思路

候选左下角只能是绿化图中的树。对每个候选，先检查窗口没有越界，再逐个查看窗口内的树是否对应藏宝图中的 `1`；最后用窗口内树总数等于藏宝图中 `1` 的数量，排除藏宝图为 `0` 但实际有树的情况。输入藏宝图从上到下给出，因此读入时倒置行号。

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

枚举候选和窗口内树的实现时间复杂度为 $O(n^2)$，藏宝图大小较小时也可视为 $O(nS^2)$；空间复杂度为 $O(n+S^2)$。

### 总结

稀疏地图不需要展开到 `L` 的平方大小；候选左下角和窗口内树数分别保证了 1、0 两种格子都被检查。
