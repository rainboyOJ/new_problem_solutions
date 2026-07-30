---
oj: "noi_openjudge"
problem_id: "ch0303-1696"
title: "波兰表达式"
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
source: http://noi.openjudge.cn/ch0303/1696/
---

<!-- generated from noiopenjudge local cache -->

[[TOC]]

### 题意

完整题面见同目录的 `problem.md`。

### 思路

#### 解析


非递归的写法,需要使用栈来实现,

如果栈最上面的三个元素,分别是

- 操作符
- 数字a
- 数字b

就可以直接运算得到结果c,然后加入到栈内,但是不好写代码,因为栈内的元素的类型不一样.


如果使用递归来写,代码就会变得很简单,递归本质就是栈.

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

<!-- 原解析未提供复杂度说明时，后续人工补充。 -->

### 总结

<!-- 保留原解析内容，不额外编造结论。 -->
