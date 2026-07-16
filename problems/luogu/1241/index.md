---
oj: "luogu"
problem_id: "P1241"
title: "括号序列"
description: "按题意用栈匹配最近未匹配左括号，记录成功位置并为其余括号补出对应一对。"
difficulty: "普及-"
date: 2026-07-16 18:10
toc: true
tags: ["栈", "字符串", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1241
---

[[TOC]]

### 题意

按指定规则从左到右给括号配对：右括号只检查左侧最近的未匹配左括号，类型相同才匹配。最后为每个未匹配括号在旁边补一个对应括号。

### 思路

栈保存尚未匹配的左括号下标。遇到右括号时，只看栈顶：类型相同则弹栈并标记两个位置；类型不同则当前右括号匹配失败，栈顶左括号仍保持未匹配，不能越过它去找更早括号。

扫描结束后按原顺序输出。已匹配字符原样保留；未匹配的 `(` 或 `)` 输出 `()`，未匹配的 `[` 或 `]` 输出 `[]`。

### Python 知识

- 列表保存下标栈，`stack[-1]` 取得最近未匹配左括号。
- 字典 `opening_for` 表示右括号所需的左括号，`completion` 表示每种未匹配字符的补全结果。
- `matched[index] = matched[stack.pop()] = True` 同时标记一对位置。
- 最终用生成器和 `"".join` 构造字符串，避免循环中反复拼接。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串不可变与 `join`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：按条件生成输出片段。

### 代码

@include-code(./main.py, python)

### 复杂度

每个字符最多入栈、出栈一次，时间和空间复杂度均为 $O(|s|)$。

### 总结

本题规则与普通“遇到不匹配就弹栈”不同：右括号只能检查最近未匹配左括号，类型不符时两者都保留为未匹配。
