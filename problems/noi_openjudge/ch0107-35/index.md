---
oj: "noi_openjudge"
problem_id: "ch0107-35"
title: "字符串的展开"
description: "逐个处理连字符，仅对合法同类递增区间按三个参数生成展开内容。"
difficulty: "普及/提高-"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "模拟", "分类讨论", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/35/
---

[[TOC]]

### 题意

根据 $p1,p2,p3$ 展开合法的字母或数字递增区间，处理大小写、重复次数和逆序规则。

### 思路

扫描到连字符时，先判断两侧是否同类且严格递增；不合法则保留 `-`。合法时枚举两端之间的字符，按 `p1` 改写、按 `p2` 重复，再按 `p3` 决定是否整体逆序。两端字符由普通扫描自然保留。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

<!-- 原解析未提供复杂度说明时，后续人工补充。 -->

### 总结

<!-- 保留原解析内容，不额外编造结论。 -->
## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设输出长度为 $L$，时间复杂度为 $O(L)$，额外空间复杂度为 $O(L)$。

### 总结

字符串展开题的难点在合法区间判定；把无效连字符先原样保留，可明显简化后续逻辑。
