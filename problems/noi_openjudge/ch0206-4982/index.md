---
oj: "noi_openjudge"
problem_id: "ch0206-4982"
title: "踩方格"
description: "题意与原解析均从本地 OpenJudge 缓存迁移。"
difficulty: "未知"
date: 2026-07-30 23:01
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0206/4982/
---

<!-- generated from noiopenjudge local cache -->

[[TOC]]

### 题意

完整题面见同目录的 `problem.md`。

### 思路

#### 解析

就是数字金字塔

可以想到这里就是dfs走迷宫,于是上来就写一个dfs的代码,这个代码可以作为验证数据是否正确.



#### dp思想

dp第一步,就是分阶段,也就是确定 题目没有后效性,也就是不能"回头",也就是不能回到过去

针对这个题目,显然每上一层,就不能回到下一层了,从层上来说,就符合DP.

假如局限在这一行,显然这个点一旦向右走,就不能回头






#### 错误的代码

考虑的状态不对,没有考虑到,起点上面的格式,可以3步走到

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

<!-- 原解析未提供复杂度说明时，后续人工补充。 -->

### 总结

<!-- 保留原解析内容，不额外编造结论。 -->
