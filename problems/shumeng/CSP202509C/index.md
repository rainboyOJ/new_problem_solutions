---
oj: "shumeng"
problem_id: "CSP202509C"
title: "HTTP 头信息"
description: "恢复 Huffman 树并解码字段字符串，用双端队列模拟动态表的前插和容量淘汰。"
difficulty: "普及/提高-"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "字符串", "二叉树", "队列"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202509C
---

[[TOC]]

### 题意

输入静态表、动态表容量、Huffman 树和一系列 HPACK 指令，输出每条指令解码得到的 `key: value`。指令可能引用表项、使用字面量并索引或使用字面量但不索引。

### 思路

先按先序递归解析 Huffman 树：`0` 后递归左右子树，`1` 后读取一个字符作为叶子。解码 Huffman 字符串时逐位沿树走到叶子；末尾字节给出了需要忽略的补零位。普通字符串以非 `H` 开头，`HH...` 表示去掉一个转义用的 `H`。

静态表用数组保存，动态表用 `deque` 保存。编号不超过 `S` 时访问静态表，否则转换为动态表下标；并索引指令先输出，再把新条目插入动态表最前面，超容量时删除末尾。

小数据参考程序直接运行同一套表格模拟器：

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设所有输入字符串长度总和为 `L`，时间复杂度为 `O(L+N)`，动态表操作为 `O(D)` 以内，空间复杂度为 `O(L+D)`。

### 总结

本题把编码树恢复、二进制字符串解码和有限动态表模拟组合在一起；按输入协议逐层拆分即可避免混淆。
