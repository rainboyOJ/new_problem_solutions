---
oj: "leetcodecn"
problem_id: "decode-string"
title: "字符串解码"
description: "遇到 [ 时保存当前字符串和次数到栈，遇到 ] 时弹出并拼接重复结果，处理嵌套编码。"
difficulty: "普及+/提高"
date: 2026-07-29 12:08
toc: true
tags: ["栈", "字符串"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/decode-string/
---

[[TOC]]

### 题意

解码 `k[encoded_string]` 格式的字符串，支持嵌套。`k` 为正整数，`encoded_string` 重复 `k` 次。

### 思路

扫描字符串，维护当前构建的字符串 `cur` 和当前累积的数字 `num`：

- 数字：累积到 `num`（处理多位次数）。
- `[`：保存 `cur` 和 `num` 到栈，重置两者——开始处理内层编码。
- `]`：弹出栈顶的前缀字符串和次数，`cur = 前缀 + cur × 次数`——内层解码完成，回到外层。
- 字母：直接追加到 `cur`。

栈保存的是"遇到 `[` 时的外层状态"，`]` 时恢复并合并内层结果。嵌套编码的栈深度等于嵌套层数。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n \cdot k_{\max})$，解码后字符串长度可能远大于输入。
- 空间复杂度：$O(d)$，栈深度等于嵌套层数。

### 总结

嵌套编码的解码用栈保存外层状态：遇到 `[` 保存当前字符串和次数，遇到 `]` 恢复并拼接。关键理解 `[` 是"进入内层"的信号，`]` 是"回到外层并合并结果"的信号。
