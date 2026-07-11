---
oj: "usaco"
problem_id: "1107"
title: "Year of the Cow"
description: "把 Bessie 设为第 0 年，用牛名到相对年份的映射和生肖模 12 关系逐条推导 Elsie 年份。"
difficulty: "入门"
date: 2026-07-11 13:29
toc: true
tags: ["模拟", "字符串"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1107
---

[[TOC]]

### 题意

给定若干条牛之间出生年份的关系，例如某头牛出生在另一头牛之前或之后最近的某个生肖年。

Bessie 出生在 Ox 年。要求推导 Elsie 与 Bessie 的出生年份相差多少年。

### 思路

#### 暴力想法

把 Bessie 的出生年份设为 `0`。处理一条关系时，从参照牛的年份开始，按 `previous` 或 `next` 一年一年移动，直到遇到目标生肖：

@include-code(./brute.cpp, cpp)

这个做法很直观，因为每次最多走 12 年。

#### 用模 12 直接跳转

12 个生肖循环出现，把它们编号：

```text
Ox=0, Tiger=1, ..., Rat=11
```

如果某头牛的相对年份是 `year`，那么它的生肖就是 `year mod 12`。

处理一条 `next` 关系时，设参照牛生肖编号为 `base_animal`，目标生肖编号为 `target_animal`：

```text
diff = (target_animal - base_animal + 12) % 12
如果 diff == 0，则 diff = 12
新牛年份 = base_year + diff
```

`previous` 同理，只是向前走：

```text
diff = (base_animal - target_animal + 12) % 12
如果 diff == 0，则 diff = 12
新牛年份 = base_year - diff
```

这里 `diff == 0` 必须改成 `12`，因为题目要求严格之前或严格之后，不能停在同一年。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每条关系处理一次，使用 `map` 查询和插入，时间复杂度为 $O(N \log N)$。

空间复杂度为 $O(N)$。

### 总结

这题的关键是用相对年份简化问题：不需要知道真实年份，只要知道每头牛相对 Bessie 是第几年。

生肖由年份对 12 的余数决定，所以每条关系都可以用一次模运算推出新牛的年份。
