---
oj: "luogu"
problem_id: "P2952"
title: "[USACO09OPEN] Cow Line S"
description: "把当前牛队维护成双端队列，左右加入和左右删除都直接映射到 deque 的头尾操作。"
difficulty: "入门"
date: 2026-06-18 14:40
toc: true
tags: ["队列", "模拟", "USACO"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2952
---

[[TOC]]

### 题意

有一列牛，初始为空。

牛会按编号 `1,2,3,...` 依次出现，每次新来的牛会加入左端或右端。

另外还会有删除操作，从左端或右端删去若干头牛。

要求输出所有操作结束后，队伍从左到右剩下的牛编号。

### 思路

先看最直接的做法：把当前队伍存在数组里。

- 左边加入就插到开头；
- 右边加入就插到末尾；
- 左边删除就删掉开头若干个；
- 右边删除就删掉末尾若干个。

这个暴力版最容易对应题目：

@include-code(./brute.cpp, cpp)

但如果用普通数组，头部插入和头部删除都可能搬动很多元素。

题目所有操作都只发生在两端，所以最合适的数据结构其实就是双端队列 `deque`：

- `A L` 对应 `push_front`
- `A R` 对应 `push_back`
- `D L K` 对应连续 `K` 次 `pop_front`
- `D R K` 对应连续 `K` 次 `pop_back`

再用一个变量 `cur` 记录下一头要加入的牛编号即可。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：$O(S)$
- 空间复杂度：$O(S)$

### 总结

这题的重点不是推公式，而是把题面操作快速映射到正确的数据结构。

只要看到“所有修改都在两端进行”，就应该优先想到双端队列。
