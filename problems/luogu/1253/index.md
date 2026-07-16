---
oj: "luogu"
problem_id: "P1253"
title: "扶苏的问题"
description: "在线段树中同时维护区间赋值、区间加法和区间最大值。"
difficulty: "普及+/提高"
date: 2026-07-16 23:59
toc: true
tags: ["线段树", "懒标记", "区间赋值", "区间最大值", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1253
---

[[TOC]]

### 题意

支持把区间全部赋为 `x`、把区间全部加上 `x`，以及查询区间最大值。

### 思路

节点保存最大值，并维护两个标记：未下传的赋值 `assigned` 和追加加法 `addition`。赋值会覆盖旧的加法；加法若遇到已有赋值就直接改写赋值，否则累加到 `addition`。下传时先赋值、后加法。

### Python 知识

- `bytearray` 保存“是否存在赋值标记”，因为赋值本身可能是负数，不能用数值正负判断。
- `array("q")` 紧凑保存最多四百万个 64 位线段树字段，控制百万规模数据的内存。
- `(set_value if operation == 1 else add_value)(...)` 用函数对象选择两种更新。
- 查询初值取很小的负数，能够正确处理全负数区间。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

建树 `O(n)`，每次更新或查询 `O(log n)`，空间 `O(n)`。

### 总结

多个懒标记共存时，先写清楚“新操作作用在旧标记之后”的复合顺序，代码就不会混乱。
