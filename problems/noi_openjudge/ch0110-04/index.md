---
oj: "noi_openjudge"
problem_id: "ch0110-04"
title: "奖学金"
description: "计算总分后按总分、语文分和学号组成的三元键排序。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["排序", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0110/04/
---

[[TOC]]

### 题意

每个学生有语文、数学、英语三科成绩。按总分降序、语文降序、学号升序的规则排列，输出前五名的学号和总分。

### 思路

读入时顺便计算总分，并保存 `(学号, 语文, 总分)`。排序键为 `(-总分, -语文, 学号)`：前两项取相反数得到降序，学号保持正数得到升序。排序结果前五项就是答案。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n \log n)$，空间复杂度为 $O(n)$。

### 总结

多级排名不必手写比较函数，把各优先级按顺序放进排序键即可。
