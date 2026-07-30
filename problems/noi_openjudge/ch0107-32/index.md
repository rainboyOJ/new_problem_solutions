---
oj: "noi_openjudge"
problem_id: "ch0107-32"
title: "行程长度编码"
description: "先统一为大写，再按连续相同字符分段输出行程长度编码。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/32/
---

[[TOC]]

### 题意

对大小写不敏感的字母串做行程长度编码，格式为 `(字符,次数)`。

### 思路

先 `upper()` 使大小写相同的字母合并，再用与 p 型编码相同的连续段扫描，按要求拼出括号格式。

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

时间复杂度为 $O(n)$，输出空间为 $O(n)$。

### 总结

先做规范化，再做分段统计，可使“大小写不敏感”不干扰主循环。
