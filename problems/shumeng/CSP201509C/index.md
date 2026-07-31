---
oj: "shumeng"
problem_id: "CSP201509C"
title: "模板生成系统"
description: "扫描模板中的 {{ VAR }} 标记，用变量表中的值做一次非递归替换。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["字符串", "模拟"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201509C
---

[[TOC]]

### 题意

按变量定义表替换模板中的 `{{ VAR }}` 标记；未定义变量替换为空串，替换结果不再递归处理。

### 思路

基准程序反复定位下一处标记：

@include-code(./brute.cpp, cpp)

读入变量定义后存入映射表。逐行扫描模板，普通字符直接复制；遇到 `{{ ` 时找到对应的 ` }}`，取出变量名并拼接映射值。每个标记只从原模板读取一次，因此变量值中的标记不会再次被替换。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设模板总长度为 $L$，时间复杂度为 $O(L\log n)$，空间复杂度为 $O(L+n)$。

### 总结

模板替换要区分原文本和已经输出的变量值。始终扫描原模板即可自然满足“不递归生成”。
