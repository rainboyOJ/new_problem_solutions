---
oj: "usaco"
problem_id: "1347"
title: "Candy Cane Feast"
description: "维护当前糖棒已被吃到的高度，依次模拟每头牛能吃到的区间并更新身高。"
difficulty: "普及-"
date: 2026-07-11 12:56
toc: true
tags: ["模拟"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1347
---

[[TOC]]

### 题意

有 $N$ 头牛，每头牛有一个当前身高。

FJ 依次把 $M$ 根糖棒竖直挂起来，从地面开始。每根糖棒都会让牛按编号顺序尝试吃。

一头牛最多只能吃到自己当前身高能触及的位置；吃掉多少糖棒，她的身高就增加多少。

求所有糖棒喂完后每头牛的最终身高。

### 思路

#### 暴力想法

按题意模拟即可。

对当前糖棒维护一个变量 `eaten`，表示从地面到高度 `eaten` 的部分已经被吃掉了。

一头牛高度为 `h`：

- 如果 `h <= eaten`，她吃不到；
- 如果 `h > eaten`，她能吃掉从 `eaten` 到 `min(h,candy)` 的部分。

这个直接模拟版本适合理解题意：

@include-code(./brute.cpp, cpp)

#### 提前停止

如果 `eaten == candy`，说明当前糖棒已经完全被吃完，后面的牛不可能再吃到。

所以正解只需要在当前糖棒吃完时退出这一轮，进入下一根糖棒。

更新过程是：

```text
top = min(height_cow[i], candy)
add = top - eaten
height_cow[i] += add
eaten = top
```

这里 `add` 就是第 `i` 头牛实际吃掉的长度。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

使用一个变量维护当前糖棒状态，空间复杂度 $O(N)$。

官方解析说明，在糖棒吃完后提前停止的模拟可以通过本题数据范围。
注意所有高度和增长量都要使用 `long long`。

### 总结

这题的关键是把糖棒剩余状态压缩成一个高度 `eaten`。

每头牛只会影响从 `eaten` 到自己能触及高度之间的区间，更新这个高度后继续模拟即可。
