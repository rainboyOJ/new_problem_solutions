---
oj: "luogu"
problem_id: "P3056"
title: "[USACO12NOV] Clumsy Cows S"
description: "从左到右统计前缀失衡次数，再用剩余的左括号数量除以二补上最少翻转数。"
difficulty: "普及-"
date: 2026-06-18 15:44
toc: true
tags: ["栈", "贪心", "USACO"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3056
---

[[TOC]]

### 题意

给定一个括号串，每次可以把一个 `(` 翻成 `)` 或把一个 `)` 翻成 `(`。

要求最少翻转多少次，才能让字符串变成合法括号串。

### 思路

先看最直接的办法：枚举哪些位置翻转，然后检查括号串是否平衡。

这个做法最容易理解：

@include-code(./brute.cpp, cpp)

下面是另一种「01 序列」风格的暴力写法。它按位置依次决定当前括号翻或不翻，递归生成完整选择后，叶子节点统一检查括号串是否合法，并统计最少翻转次数：

<details>
<summary>另一种暴力写法：01 序列</summary>

@include-code(./brute_01_style.cpp, cpp)

</details>

但显然不能直接用来做正解。

这题的关键在于前缀性质。

扫描字符串时维护 `balance = 左括号数 - 右括号数`：

- 遇到 `(`，`balance++`
- 遇到 `)`，`balance--`

如果某一步 `balance < 0`，说明当前前缀里右括号太多了，后面再怎么补都救不回这个前缀，所以必须立刻把当前这个 `)` 翻成 `(`。

翻完以后，当前前缀就从 `-1` 变成了 `1`，因此：

- `ans++`
- `balance = 1`

扫描结束后，如果 `balance > 0`，说明还有多余的左括号。每两个左括号可以通过一次翻转变成一对合法括号，所以还要再加上 `balance / 2`。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：$O(n)$
- 空间复杂度：$O(1)$

### 总结

这题的核心不是枚举翻转位置，而是利用前缀合法性做贪心。

一旦前缀失衡，就必须立即修正当前右括号；剩下的多余左括号再统一成对处理即可。
