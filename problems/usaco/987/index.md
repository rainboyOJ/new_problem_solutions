---
oj: "usaco"
problem_id: "987"
title: "Word Processor"
description: "顺序扫描单词，维护当前行非空格字符数，放不下时换行输出。"
difficulty: "入门"
date: 2026-07-11 14:24
toc: true
tags: ["模拟", "字符串"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=987
---

[[TOC]]

### 题意

给定 `N` 个单词和每行字符上限 `K`。

需要按顺序输出这些单词，使每一行的非空格字符数不超过 `K`。如果下一个单词放入当前行会超过 `K`，就把它放到下一行。

同一行单词之间用一个空格分隔，行末不能有多余空格。

### 思路

#### 朴素模拟

可以先把每一行的单词保存下来，最后统一输出：

@include-code(./brute.cpp, cpp)

这个写法非常直观：每个单词要么加入当前行，要么新开一行。

#### 边扫描边输出

正式代码可以不保存所有行，只维护一个变量：

```text
current_len = 当前行已有的非空格字符数量
```

对每个单词 `w`：

- 如果 `current_len + len(w) > K`，先输出换行，再输出 `w`；
- 否则把 `w` 放在当前行，如果当前行已有单词，就在它前面输出一个空格。

注意空格不计入 `current_len`，所以更新长度时只加单词长度。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每个单词处理一次，时间复杂度为 $O(N)$。

保存单词数组，空间复杂度为 $O(N)$。

### 总结

这题的关键是分清“输出时需要空格”和“判断长度时不统计空格”。

只要维护当前行已有多少个非空格字符，就能直接模拟题目规则。
