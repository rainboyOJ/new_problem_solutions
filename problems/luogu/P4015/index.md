---
oj: "luogu"
problem_id: "P4015"
title: "运输问题"
difficulty: "提高+/省选-"
date: 2026-01-31 12:57
toc: true
tags: []
desc: ""
pre:
  - oj: "luogu"
    problem_id: "P4014"
    reason: "先掌握费用流（MCMF）的基本建模和费用取反技巧，再处理多源多汇的运输供需匹配。"
common:
  - oj: "luogu"
    problem_id: "P4014"
    reason: "同为基本费用流供需匹配建模题，P4014 为二分图完美匹配，P4015 为多仓库多商店的一般运输模型。"
source: https://www.luogu.com.cn/problem/P4015
---

[[TOC]]

## 题目解析

> 这个题目可以说是: luogu 4016 的简化版本, 直接建立图

## 代码 

@include-code(./1.cpp, cpp)

