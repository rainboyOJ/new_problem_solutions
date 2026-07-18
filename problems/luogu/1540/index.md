---
oj: "luogu"
problem_id: "P1540"
title: "[NOIP 2010 提高组] 机器翻译"
description: "用队列维护单词进入内存的先后顺序，再用标记数组判断当前是否命中内存。"
difficulty: "普及-"
date: 2026-06-18 14:16
toc: true
tags: ["队列", "模拟", "noip", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1540
---

[[TOC]]

### 题意

有一篇文章，按顺序给出 `N` 个单词编号。

翻译软件的内存最多只能存 `M` 个单词：

- 如果当前单词已经在内存里，就直接使用，不查词典；
- 如果不在内存里，就要查一次词典，并把它放入内存；
- 如果内存已满，就删掉最早进入内存的那个单词，再把新单词放进去。

要求统计总共查了多少次词典。

### 思路

先看一个最朴素的模拟：直接用数组保存当前内存中的单词。

每次读到一个单词，就在线性扫描数组里找它是否已经存在；如果不存在，答案加一，必要时删掉数组最前面的单词，再把当前单词放到数组末尾。

这个写法直观、容易验证：

@include-code(./brute.cpp, cpp)

不过它每次都要在线性扫描当前内存，不够干净。

题目真正的结构其实很明确：

- 新单词进入内存时，总是放到最后面；
- 内存满了时，总是删掉最早进入内存的单词。

这正是队列的先进先出模型。

所以我们可以：

- 用队列保存“当前内存里的单词进入顺序”；
- 用 `in_memory[x]` 记录单词 `x` 当前是否已经在内存中。

这样每次处理一个单词时：

- 若 `in_memory[x]` 为真，说明命中，直接跳过；
- 否则答案加一；
- 如果队列已满，先弹出队头并清除它的存在标记；
- 再把新单词压入队尾。

这题也正好被 rbook 的《队列》文章列为基础队列模拟例题：
<https://rbook2.roj.ac.cn/data-structure/queue/index.html>

### Python 知识

- `deque` 维护 FIFO 淘汰顺序，`set` 维护当前是否命中；两种容器各负责一种操作。
- `word in memory` 平均 $O(1)$，避免每次扫描整个队列。
- 淘汰时 `memory.remove(order.popleft())` 把队首值直接从集合中同步删除。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`set` 判重与 `deque` 队列。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

deque：

@include-code(./main-pythonic.py, python)

### 复杂度

- 时间复杂度：$O(n)$
- 空间复杂度：$O(m)$

### 总结

这题的关键是识别出“淘汰最早进入内存的单词”这一条规则。

一旦看出它是 FIFO 缓存，就可以自然地想到“队列维护顺序，标记数组维护是否存在”的做法。
