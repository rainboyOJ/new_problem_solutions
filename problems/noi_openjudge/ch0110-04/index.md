---
oj: "noi_openjudge"
problem_id: "ch0110-04"
title: "奖学金"
description: "计算总分后按总分、语文分和学号组成的三元键排序。"
difficulty: "普及-"
date: 2026-07-30 23:01
updated: 2026-10-07 12:15
toc: true
tags: ["排序", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre:
  - oj: "noi_openjudge"
    problem_id: "ch0110-01"
    reason: "B 沿用 A 的把学生记成元组后按成绩排序取名次这一步，扩成总分、语文、学号三关键字并取前五名"
  - oj: "noi_openjudge"
    problem_id: "ch0110-03"
    reason: "B 直接复用 A 的「多级排序键用元组加负号转降序」这一步写法，只是从两级规则扩到三级（总分降序、语文降序、学号升序）"
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
