---
oj: "usaco"
problem_id: "1419"
title: "Logical Moos"
description: "按 or 把表达式分成 and 组，维护每组 false 位置和区间外 true 组来 O(1) 回答替换询问。"
difficulty: "普及-"
date: 2026-07-11 12:39
toc: true
tags: ["模拟", "字符串"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1419
---

[[TOC]]

### 题意

给定一个布尔表达式，奇数位置是 `true/false`，偶数位置是 $and/or$。
求值时 `and` 优先级高于 `or`。

每次询问给出一段 `[l,r]`，删除这段 token，并用一个单独的 `true` 或 `false` 替换。
问是否存在一种替换值，使整个表达式的结果等于询问给定的目标值。

### 思路

#### 暴力想法

对每个询问，可以分别尝试把 `[l,r]` 替换成 `true` 和 `false`，然后重新计算表达式。

计算表达式时，先把连续的 `and` 段算成一个布尔值，再把这些值用 `or` 合并。

这个暴力适合小数据和对拍：

@include-code(./brute.cpp, cpp)

每个询问重新计算一次表达式需要 $O(N)$，满分数据中 $N,Q$ 都很大，需要进一步预处理。

#### 按 `or` 分组

因为 `and` 优先级高于 `or`，可以把表达式按 `or` 切成若干个 group。

例如：

```text
false and true or true
```

等价于：

```text
(false and true) or (true)
```

一个 group 是若干个布尔值用 `and` 连接。
它为 `true` 当且仅当组内没有 `false`。
整个表达式为 `true` 当且仅当至少一个 group 为 `true`。

#### 回答询问

对每个布尔位置预处理它属于哪个 group。
对每个 group 记录：

- 第一个 `false` 的位置；
- 最后一个 `false` 的位置。

同时记录原表达式中最左和最右的 true group。

询问 `[l,r]` 时，设：

```text
gl = group[l]
gr = group[r]
```

如果 `gl` 左边或 `gr` 右边存在 true group，那么无论替换什么，整个表达式都一定为 `true`。
因此目标为 `true` 时可行，目标为 `false` 时不可行。

否则，区间外所有 group 都是 `false`。
如果目标是 `false`，直接把删除段替换成 `false` 即可。

如果目标是 `true`，只能靠替换后新形成的 group 变成 `true`。
这要求它没有残留的 `false`：

```text
gl 中不能有 false 在 l 左边
gr 中不能有 false 在 r 右边
```

用 `first_false[gl]` 和 `last_false[gr]` 就能 $O(1)$ 判断。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

预处理时间复杂度 $O(N)$。

每个询问 $O(1)$ 回答，总时间复杂度 $O(N+Q)$。

空间复杂度 $O(N)$。

### 总结

这题的关键是把布尔表达式转成“多个 and-group 做 or”的结构。

一旦知道每个 group 是否含有 `false`，以及查询区间外是否已经有 true group，就可以把替换询问化成几个位置比较。
