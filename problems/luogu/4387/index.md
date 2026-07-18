---
oj: "luogu"
problem_id: "P4387"
title: "【深基15.习9】验证栈序列"
description: "按入栈序列依次压栈，并在每次压栈后尽可能把栈顶与目标出栈序列匹配。"
difficulty: "普及-"
date: 2026-06-18 16:10
toc: true
tags: ["栈", "模拟", "深基", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4387
---

[[TOC]]

### 题意

给出入栈序列 `pushed` 和出栈序列 `poped`。

判断 `poped` 是否可能是按照栈的先进后出规则，由 `pushed` 模拟得到的出栈序列。

### 思路

最直接的做法是递归枚举每一步是“入栈”还是“出栈”。

这个版本只适合小数据验证：

@include-code(./brute.cpp, cpp)

但这题其实不需要搜索。

因为栈的行为是确定的：

- 先按 `pushed` 顺序入栈；
- 每次只要栈顶和 `poped` 当前元素相同，就立刻出栈。

所以只需要一个栈和一个指针 `j`：

1. 遍历 `pushed` 中的每个元素；
2. 先把它压入栈；
3. 然后只要栈顶等于 `poped[j]`，就持续弹栈；
4. 最后如果栈为空，说明 `poped` 合法。

### Python 知识

- 普通列表就是竞赛中最常用的栈：`append` 压栈，`pop` 弹栈，`stack[-1]` 访问栈顶。
- `tokens` 整数迭代器连续读取多组不同长度的数据。
- `while stack and ...` 利用短路顺序保证空栈时不会访问 `stack[-1]`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：token 迭代读取多组数据。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：短路条件与可迭代数据。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sys.stdin 快读：

@include-code(./main-pythonic.py, python)

### 复杂度

- 时间复杂度：$O(n)$
- 空间复杂度：$O(n)$

### 总结

这题的核心是“模拟栈的真实行为”，而不是枚举所有可能操作。

只要栈顶一旦能匹配目标出栈序列，就应该立刻出栈。

### 一图流解析

这张图把本题的建模、关键转移、实现检查和训练方法压缩到一页，适合读完正文后复盘。

![一图流解析](./one-page-explainer.png)
