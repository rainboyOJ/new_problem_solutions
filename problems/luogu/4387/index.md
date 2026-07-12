---
oj: "luogu"
problem_id: "P4387"
title: "【深基15.习9】验证栈序列"
description: "按入栈序列依次压栈，并在每次压栈后尽可能把栈顶与目标出栈序列匹配。"
difficulty: "普及-"
date: 2026-06-18 16:10
toc: true
tags: ["栈", "模拟", "深基"]
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

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：$O(n)$
- 空间复杂度：$O(n)$

### 总结

这题的核心是“模拟栈的真实行为”，而不是枚举所有可能操作。

只要栈顶一旦能匹配目标出栈序列，就应该立刻出栈。

### 一图流解析

这张图把本题的建模、关键转移、实现检查和训练方法压缩到一页，适合读完正文后复盘。

![一图流解析](./one-page-explainer.png)
