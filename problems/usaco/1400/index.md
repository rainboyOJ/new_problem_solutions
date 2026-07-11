---
oj: "usaco"
problem_id: "1400"
title: "Moorbles"
description: "先把每轮压成最坏变化量，倒推后缀安全线，再从前往后贪心选择字典序最小操作。"
difficulty: "普及+/提高"
date: 2026-07-11 21:05
toc: true
tags: ["贪心", "后缀和", "模拟", "usaco"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1400
---

[[TOC]]

### 题意

Elsie 每轮要猜 Bessie 取出的弹珠数 $A$ 是偶数还是奇数。

如果猜对，Elsie 从 Bessie 那里赢得 $A$ 个弹珠；如果猜错，Elsie 输掉 $A$ 个弹珠。某个玩家弹珠数变成 $0$ 时失败。

现在已知接下来每一轮 Bessie 只会从给定的 $K$ 个数中选择一个。要求输出一个字典序最小的 `Even/Odd` 序列，使得无论 Bessie 每轮怎么选，Elsie 都不会输。如果不存在，输出 `-1`。

### 思路

先看小数据暴力：把每一轮看成一次二选一，递归枚举完整的 `Even/Odd` 序列，再检查它是否安全。

@include-code(./brute.cpp, cpp)

暴力能直接体现字典序：每一层先选 `Even`，再选 `Odd`。但序列数量是 $2^M$，必须优化。

先把每一轮压成两个“最坏变化量”：

| 数组 | 含义 |
| --- | --- |
| `change[i][0]` | 第 `i` 轮猜 `Even` 时，Bessie 最坏选择下 Elsie 的弹珠变化 |
| `change[i][1]` | 第 `i` 轮猜 `Odd` 时，Bessie 最坏选择下 Elsie 的弹珠变化 |

猜对时，Bessie 会让 Elsie 赢得尽量少；猜错时，Bessie 会让 Elsie 输得尽量多。

接下来倒着计算安全线：

```text
need[i] = 第 i 轮开始前，弹珠数必须严格大于多少，才存在后续不输策略
```

结束后不需要额外弹珠，所以：

```text
need[M] = 0
```

第 `i` 轮如果只考虑“后面还能活下去”，Elsie 会选择两个变化量中更好的一个。因此：

```text
need[i] = max(0, need[i+1] - max(change[i][0], change[i][1]))
```

这里要注意是“严格大于 `need[i]`”才安全，因为弹珠数等于 $0$ 已经输了。

有了 `need` 后，从前往后构造答案。每一轮先尝试字典序更小的 `Even`：

```text
如果 current + change[i][0] > need[i+1]，选 Even
否则选 Odd
```

如果 `Even` 后仍然高于下一轮安全线，说明后面一定存在安全策略，所以可以放心选 `Even`；否则所有以这个前缀接 `Even` 的方案都不可能安全，只能选 `Odd`。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每轮只处理 $K$ 个可能值，并维护两个变化量。

时间复杂度为 $O(MK)$。

空间复杂度为 $O(M)$。

### 总结

本题的关键是先把 Bessie 的所有选择压成“最坏情况下的变化量”，再倒推后缀安全线。

字典序最小不是最后排序出来的，而是在每一轮用安全线判断：能选 `Even` 就立刻选 `Even`，不能选才选 `Odd`。
