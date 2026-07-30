---
oj: "noi_openjudge"
problem_id: "ch0103-08"
title: "温度表达转化"
description: "按 C=5(F-32)/9 计算摄氏温度并保留五位小数。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0103/08/
---

[[TOC]]

### 题意

把输入的华氏温度 $F$ 转换为摄氏温度 $C$，保留 5 位小数。

### 思路

直接代入 $C=5(F-32)/9$。Python 的 `/` 不会做整数截断，所以不必额外把常量写成小数；最后用 `.5f` 控制输出。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度和额外空间复杂度均为 $O(1)$。

### 总结

单位换算题的算法就是忠实保留公式括号，再根据题目要求格式化结果。
