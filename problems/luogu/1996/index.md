---
oj: "luogu"
problem_id: "P1996"
title: "约瑟夫问题"
description: "用队列模拟报数过程，队头出队后要么出列，要么重新回到队尾。"
difficulty: "入门"
date: 2026-06-18 14:04
toc: true
tags: ["队列", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1996
---

[[TOC]]

### 题意

有 `n` 个人围成一圈，编号是 `1` 到 `n`。

从 `1` 号开始报数，每次数到第 `m` 个，这个人就出列；下一个还在圈里的人重新从 `1` 开始报数。

要求输出所有人的出列顺序。

### 思路

先看一个最直接的做法：把所有还在圈里的人放在数组里，每次根据当前位置往后数 `m` 个，找到要删除的人并从数组中移除。

这个方法容易理解，也方便对拍：

@include-code(./brute.cpp, cpp)

但这种写法每次删除都要移动一段数组元素，不太适合作为这道队列题的标准思路。

更自然的想法是把当前还在圈里的人放进队列里：

- 每次取出队头，表示当前轮到这个人报数；
- 如果他报到第 `m` 个，就直接输出，不再入队；
- 否则把他重新放回队尾，表示他还留在圈里，等待下一轮。

题目的“围成一圈”就被转成了“队头出队，没出列的人回到队尾”的过程。

如果你想先补一下队列的基础直觉，可以参考 rbook 里的《队列》一文：
<https://rbook2.roj.ac.cn/data-structure/queue/index.html>

### Python 知识

- `deque(range(1,n+1))` 直接建立初始圆圈。
- `circle.rotate(-(m-1))` 把即将出列的人转到队首，再用 `popleft()` 删除；这比逐人出队再入队更贴近“整体旋转圆圈”。
- `print(*order)` 用空格展开出列顺序。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`deque` 的双端操作。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

deque + print*：

@include-code(./main-pythonic.py, python)

### 复杂度

- 时间复杂度：$O(nm)$ 量级，足够通过本题。
- 空间复杂度：$O(n)$。

### 总结

这题的关键不是公式，而是把“围成一圈不断报数”的过程翻译成合适的数据结构操作。

只要意识到“当前人处理完后，要么删除，要么回到最后面”，就很容易想到用队列模拟。
