---
oj: "noi_openjudge"
problem_id: "ch0110-08"
title: "病人排队"
description: "用排序键同时表达老人优先、年龄降序和登记顺序保持规则。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["排序", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0110/08/
---

[[TOC]]

### 题意

老人（年龄不小于 60 岁）优先看病，老人中年龄大的在前、同龄保持登记顺序；非老人全部保持登记顺序。

### 思路

保存 `(编号, 年龄, 登记顺序)`。排序键的第一项 `年龄 < 60` 对老人是 `False`、对非老人是 `True`，所以老人排在前；第二项只有对老人使用 `-年龄`，让老人年龄降序；最后的登记顺序保证同龄老人和所有非老人都按原顺序排列。

Python 的排序本身稳定，但把登记顺序写进键中能将全部规则明确地表达出来。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n \log n)$，空间复杂度为 $O(n)$。

### 总结

遇到“优先级 + 保持原顺序”的规则，可将优先级和原始下标依次放入排序键。
