---
oj: "noi_openjudge"
problem_id: "ch0107-22"
title: "紧急措施"
description: "筛选邮箱相同的账号，并用 swapcase 输出修改后的密码。"
difficulty: "入门"
date: 2026-07-30 23:01
toc: true
tags: ["字符串", "模拟", "筛选", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/22/
---

[[TOC]]

### 题意

从账号列表中找出指定邮箱的账号，输出用户名和大小写互换后的密码；没有账号则输出 `empty`。

### 思路

逐条比较邮箱。匹配时调用 `password.swapcase()` 并保存结果，循环后按换行连接；结果列表为空时输出 `empty`。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设所有账号字段长度总和为 $n$，时间复杂度为 $O(n)$，输出空间为 $O(n)$。

### 总结

筛选记录时先收集，再统一决定空结果与多行输出格式。
