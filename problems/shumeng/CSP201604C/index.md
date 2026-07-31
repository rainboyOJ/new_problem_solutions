---
oj: "shumeng"
problem_id: "CSP201604C"
title: "路径解析"
description: "用目录组件栈处理绝对路径、相对路径、.、.. 与连续斜杠。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["字符串", "栈", "模拟"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201604C
---

[[TOC]]

### 题意

将给定路径正规化为无 `.`、`..` 和连续斜杠的绝对路径。

### 思路

把路径按 `/` 分成目录组件并维护栈。绝对路径从空栈开始，相对路径从当前目录组件开始；`.` 与空组件跳过，`..` 弹出一层但根目录不动，普通名字入栈。最后用 `/` 重新连接组件。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设路径长度为 $L$，时间复杂度为 $O(L)$，空间复杂度为 $O(L)$。

### 总结

连续斜杠对应空组件，末尾斜杠也自然被忽略。栈为空时输出唯一的根目录 `/`。
