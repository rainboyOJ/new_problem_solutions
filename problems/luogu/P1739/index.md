---
oj: "luogu"
problem_id: "P1739"
title: "表达式括号匹配"
description: "扫描表达式时维护左括号数量，遇到右括号必须能匹配，结束时数量归零才合法。"
difficulty: "入门"
date: 2026-07-06 20:42
updated: 2026-10-07 10:45
toc: true
tags: ["栈", "字符串", "模拟"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1739
---

[[TOC]]

### 题意

给出一个以 `@` 结尾的表达式，只需要检查其中的圆括号 `(` 和 `)` 是否匹配。

如果匹配，输出 `YES`，否则输出 `NO`。

### 思路

先看一个用栈的朴素写法：

@include-code(./brute.cpp, cpp)

括号匹配只关心两个条件：

1. 扫描过程中，任意一个右括号 `)` 前面都必须有还没匹配的左括号；
2. 扫描结束时，不能剩下未匹配的左括号。

因为这里只有一种括号，所以不一定真的需要保存每个左括号，只维护一个计数器 `balance` 即可：

- 遇到 `(`，`balance++`；
- 遇到 `)`，`balance--`；
- 如果 `balance < 0`，说明右括号多了；
- 最后如果 `balance != 0`，说明左括号多了。

遇到 `@` 后表达式结束，后面不再处理。

### 代码

@include-code(./main.cpp, cpp)

### STL 写法

这道题正是 cppbook 里「用栈做配对」的标准例子：用 `stack<char>` 保存还没配对上的左括号，扫到 `(` 就 `push`，扫到 `)` 时先判断栈是否为空，非空就 `pop` 掉最近的那个左括号，扫到 `@` 结束，最后栈为空才输出 `YES`。它和上面计数器写法的判断条件完全一样，区别只在于栈把「最近的左括号」真的存了下来，所以换成多种括号时只要多一张配对表，框架不用重写；代价是栈最坏要占 $O(n)$ 的空间，而计数器只用一个变量。

对应的 cppbook 章节：[stack：最后放入，最先取出](https://cppbook.roj.ac.cn/stl/container-adapters/stack/)

@include-code(./main-stl.cpp, cpp)

### 复杂度

- 时间复杂度：$O(|s|)$
- 空间复杂度：$O(1)$

### 总结

只有一种括号时，栈可以简化成计数器。过程中不能为负，最后必须归零。
