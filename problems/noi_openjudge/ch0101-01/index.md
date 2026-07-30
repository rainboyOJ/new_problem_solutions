---
oj: "noi_openjudge"
problem_id: "ch0101-01"
title: "Hello, World!"
description: "不读取输入，严格按题面要求输出 Hello, World!。"
difficulty: "入门"
date: 2026-07-30 22:43
toc: true
tags: ["输出", "字符串"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0101/01/
---

[[TOC]]

### 题意

本题没有输入。输出一行字符串 `Hello, World!`。

判题会比较输出内容，因此 `Hello` 后是英文逗号，逗号后还有一个半角空格；不能额外输出提示文字。

### 思路

这是输出格式练习，不需要计算或分支。程序的唯一工作是向标准输出写入题面指定的完整字符串：

```text
Hello, World!
```

末尾换行通常由输出语句自动添加，评测系统会接受这一行结束后的换行。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

输出的字符数固定，时间复杂度为 $O(1)$，额外空间复杂度为 $O(1)$。

### 总结

入门题也要逐字符核对输出：大小写、英文标点、空格和换行都属于输出格式的一部分。
