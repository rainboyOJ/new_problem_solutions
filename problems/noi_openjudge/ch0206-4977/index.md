---
oj: "noi_openjudge"
problem_id: "ch0206-4977"
title: "怪盗基德的滑翔翼"
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
source: http://noi.openjudge.cn/ch0206/4977/
---

<!-- generated from noiopenjudge local cache -->

[[TOC]]

### 题意

完整题面见同目录的 `problem.md`。

### 思路

本题目就是lis,所以没有什么好讲的

$$
f[i] = max(f[j]+1,1) \; j < i \land a_j < a_i
$$

注意正反算两次

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

<!-- 原解析未提供复杂度说明时，后续人工补充。 -->

### 总结

<!-- 保留原解析内容，不额外编造结论。 -->
