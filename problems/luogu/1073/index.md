---
oj: "luogu"
problem_id: "P1073"
title: "[NOIP 2009 提高组] 最优贸易"
description: "正图求从起点到每点路径上的最低买入价，反图求每点到终点路径上的最高卖出价。"
difficulty: "普及+/提高"
date: 2026-06-22 22:02
toc: true
tags: ["图论", "最短路", "动态规划", "反图", "队列松弛"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1073
---

[[TOC]]

### 题意

从城市 `1` 出发，最终到达城市 `n`。道路可能是单向或双向，城市可以重复经过。

每个城市有一个商品价格。最多进行一次交易：先在某个经过的城市买入，再在之后经过的城市卖出。要求最大利润；如果不赚钱，可以不交易，答案为 `0`。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

暴力可以先求任意两点可达性，再枚举买入点和卖出点。但满数据显然不能这么做。

关键是把“买入点”和“卖出点”的枚举压缩成两个数组。

设：

```text
min_buy[x]  = 从 1 到 x 的某条路径上能遇到的最低价格
max_sell[x] = 从 x 到 n 的某条路径上能遇到的最高价格
```

如果旅行路线经过城市 `x`，那么可以在到达 `x` 前用 `min_buy[x]` 买入，在离开 `x` 后用 `max_sell[x]` 卖出，利润候选就是：

```text
max_sell[x] - min_buy[x]
```

如何求这两个数组？

`min_buy` 沿正图从 `1` 出发松弛：

```text
min_buy[v] = min(min_buy[v], min(min_buy[u], price[v]))
```

`max_sell` 沿反图从 `n` 出发松弛：

```text
max_sell[v] = max(max_sell[v], max(max_sell[u], price[v]))
```

反图从 `n` 出发，相当于在原图中从某点走向 `n`，因此能得到“之后能卖到的最高价”。

最后枚举所有城市 `x`，取 `max_sell[x] - min_buy[x]` 的最大值即可。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

使用队列松弛传播更优信息，空间复杂度为 $O(n+m)$。

时间复杂度按实际松弛次数计，通常近似 $O(n+m)$，可以通过本题数据。

### 总结

这道题的重点是维护“先买后卖”的顺序。

正图负责处理到达某点之前的最低买入价，反图负责处理从某点之后的最高卖出价，两者在同一个城市汇合后就能得到答案候选。
