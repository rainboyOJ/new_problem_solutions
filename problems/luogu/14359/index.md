---
oj: "luogu"
problem_id: "P14359"
title: "[CSP-J 2025] 异或和"
date: 2026-02-04 09:00
toc: true
tags: ["贪心", "位运算", "前缀和"]
categories: []
pre:
  - oj: "luogu"
    problem_id: "P1803"
    reason: "经典区间贪心，P14359 的核心子问题就是最大不相交区间数量"
common: []
recommend:
  - oj: "leetcode"
    problem_id: "1546"
    title: "Maximum Number of Non-Overlapping Subarrays With Sum Equals Target"
    url: "https://leetcode.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/"
    reason: "同样用前缀值集合和尽早结束的贪心来最大化不相交合法子数组数量，只是条件从异或和换成普通和。"
    relation: "similar"
  - oj: "leetcode"
    problem_id: "1310"
    title: "XOR Queries of a Subarray"
    url: "https://leetcode.com/problems/xor-queries-of-a-subarray/"
    reason: "练习前缀异或的基础用法，先熟悉区间异或如何由两个前缀异或值推出。"
    relation: "easier"
  - oj: "codeforces"
    problem_id: "617E"
    title: "XOR and Favorite Number"
    url: "https://codeforces.com/problemset/problem/617/E"
    reason: "同样围绕前缀异或和目标值 k 统计子数组，但扩展到区间询问和计数问题，适合作为进阶练习。"
    relation: "harder"
source: https://www.luogu.com.cn/problem/P14359
description: " 贪心: 最大不相交区间数量, 数学: 异或区间和,异或前缀和"
difficulty: "普及/提高-"
---

[[TOC]]

### 题意

给定一个长度为 $n$ 的非负整数序列 $a_1, a_2, \dots, a_n$ 和一个非负整数 $k$。定义区间 $[l, r]$ 的权值为区间内所有数的异或和。需要选出尽可能多的**不相交**区间，使每个区间的权值都等于 $k$。输出最多能选出的区间数。

#### 样例

以样例 1 为例：$n = 4, k = 2$，序列 $[2, 1, 0, 3]$。

可以选区间 $[1, 1]$（权值 $2$）和 $[2, 4]$（权值 $1 \oplus 0 \oplus 3 = 2$），答案为 $2$。

### 思路

题目要求最大化不相交区间的个数，且每个区间的权值（异或和）必须等于 $k$。由于所有区间的权重相同（均为 1），**按结束时间最早贪心**是最优策略——从左到右扫描，一旦发现可以结束一个合法区间就立即选取。

**前缀异或技巧**：令 $pre[i] = a_1 \oplus a_2 \oplus \dots \oplus a_i$，则区间 $[l, r]$ 的异或和为 $pre[r] \oplus pre[l-1]$。条件 $pre[r] \oplus pre[l-1] = k$ 等价于 $pre[l-1] = pre[r] \oplus k$。

因此，对每个右端点 $i$，只需检查 $pre[i] \oplus k$ 是否在当前段中出现过。配合哈希表可以在 $O(1)$ 时间内完成判断。

先看一个可以直接验证想法的正确解（$O(n^2)$ DP，仅适合小数据）：

@include-code(./brute.cpp, cpp)

下面是另一种「01 序列」风格的暴力写法。它先列出所有异或和为 `k` 的候选区间，再对每个候选区间决定“选 / 不选”。递归生成完整选择后，叶子节点统一检查区间是否两两不相交，并统计答案：

<details>
<summary>另一种暴力写法：01 序列</summary>

@include-code(./brute_01_style.cpp, cpp)

</details>

`brute.cpp` 的 $O(n^2)$ 瓶颈在于对每个 $i$ 都需要枚举所有 $j < i$。利用前缀异或的性质，我们将判断条件改写为 $pre[j] = pre[i] \oplus k$，从而将 $O(n^2)$ 枚举转化为 $O(1)$ 哈希查询。

具体做法：从左到右扫描，用哈希表记录当前段中出现过的所有前缀异或值。对每个位置 $i$：

1. 计算 $pre = pre \oplus a_i$
2. 查询 $target = pre \oplus k$ 是否在哈希表中
3. 如果在，说明存在某个 $j$ 使得 $[j+1, i]$ 异或和为 $k$ → 答案加 1，清空哈希表，重置 $pre = 0$
4. 如果不在，将 $pre$ 加入哈希表

清空哈希表有多种实现方式：

| 实现 | 清空方式 | 复杂度 | 得分 |
| --- | --- | --- | --- |
| 桶 + `memset` | `memset(b,0,sizeof(b))` | $O(2^{20})$ 每次 | 90 分 TLE |
| `std::map` | `b.clear()` | $O(段大小)$ | 100 分 |
| 时间戳数组 | `cur++` | $O(1)$ 每次 | 100 分 |

最终采用**时间戳数组**：开一个全局数组 $vis[x]$，用 $vis[x] = cur$ 表示 $x$ 在当前段中出现过。清空时只需 `cur++`，无需遍历数组。

下面按分值逐步展开，对照学习从 $O(n^2)$ 到 $O(n)$ 的优化过程。

## 60 分做法

### 方法一：$O(n^2)$ 贪心扫描

枚举每个位置 $i$ 作为区间右端点，从 $i$ 向前**倒着**累加异或值，检查是否存在以 $i$ 结尾、异或和为 $k$ 的区间 $[j, i]$。

P1803 贪心策略是优先选结束最早的区间。以当前 $i$ 结尾的区间是当前能选到的结束最早的合法区间，一旦找到就立即选取，跳到 $i+1$ 开始新段。

<details>
<summary>60 分：$O(n^2)$ 贪心扫描</summary>

@include-code(./1.cpp, cpp)

</details>

### 方法二：枚举所有合法区间 + P1803 区间贪心

利用异或性质 $a \oplus a = 0$，用前缀异或 $pre[r] \oplus pre[l-1]$ 快速求任意区间的异或和。

双重循环枚举所有异或和为 $k$ 的区间 $[l, r]$，每个合法区间看作一条线段。问题转化为经典的最大不相交区间问题（见 [P1803](../1803/index.md)）：按右端点从小到大排序，能选就选。复杂度 $O(n^2 + m \log m)$，$m$ 为合法区间数量，$n \leqslant 2000$ 时可接受。

<details>
<summary>60 分：枚举所有合法区间 + P1803 区间贪心</summary>

@include-code(./1_v2.cpp, cpp)

</details>

## 90 分做法

利用前缀异或将区间查询优化为 $O(1)$。用大小为 $2^{20}$ 的桶数组记录当前段中出现过的前缀异或值。每找到一个合法区间就用 `memset` 清空整个桶，代价 $O(2^{20})$ 每次，多次操作导致 TLE，只能得 90 分。

<details>
<summary>90 分：前缀异或 + memset 桶（TLE）</summary>

@include-code(./2.cpp, cpp)

</details>

## 100 分做法

核心优化是避免每轮清空大数组。时间戳技术：`vis[x]` 记录前缀异或值 $x$ 最近一次出现的时间戳 $cur$，判断 `vis[target] == cur` 即知 $target$ 是否在当前段出现过。清空只需 `cur++`，$O(1)$。

<details>
<summary>100 分：前缀异或 + std::map</summary>

@include-code(./3.cpp, cpp)

</details>

<details>
<summary>100 分：前缀异或 + 时间戳桶（最优）</summary>

@include-code(./4.cpp, cpp)

</details>

### 代码

时间戳桶的核心思想：用一个全局 `vis[]` 数组和一个不断递增的 `cur` 代替每轮清空。

```text
vis[] 数组（大小为 2^20，下标为前缀异或值）
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│  0  │  1  │  2  │  3  │ ... │  x  │ ... │MAXV │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│  2  │  0  │  0  │  0  │     │  2  │     │  0  │  ← 存储最近一次被标记的 cur 值
└─↑───┴─────┴─────┴─────┴─────┴─↑───┴─────┴─────┘
  │                              │
 vis[0]=cur                    vis[x]=cur
 表示 pre=0 在当前段出现过      表示 pre=x 在当前段出现过

判断：vis[target] == cur  →  target 在当前段出现过
清空：cur++                →  所有 vis[] 值 ≠ cur，等效于全清空
```

以样例 `[2,1,0,3], k=2` 跟踪执行过程：

```text
初始: cur=1, vis[0]=1

 i │ a[i] │ pre │ target=pre^k │ vis[target]==cur? │ 动作
───┼──────┼─────┼──────────────┼───────────────────┼───────────────
 1 │  2   │ 2   │  2^2=0       │ vis[0]=1==cur ✓   │ ans=1, cur=2, pre=0, vis[0]=2
 2 │  1   │ 1   │  1^2=3       │ vis[3]=0≠cur      │ vis[1]=2
 3 │  0   │ 1   │  1^2=3       │ vis[3]=0≠cur      │ vis[1]=2 (已在)
 4 │  3   │ 2   │  2^2=0       │ vis[0]=2==cur ✓   │ ans=2, cur=3, pre=0, vis[0]=3
```

`cur` 递增后，旧标记自动作废，无需任何 `memset` 或 `clear()`。

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：$O(n)$。每个元素处理一次，哈希查询和更新均为 $O(1)$。
- 空间复杂度：$O(2^{20}) \approx 10^6$ 的 `vis` 数组，加上 $O(n)$ 的存储输入。

### 总结

本题是 CSP-J 2025 的题目，核心模型是**单位权重区间调度 + 前缀异或哈希**。关键点在于将区间异或条件转化为前缀异或的查询，再利用贪心性质从左到右扫描。实现上，**时间戳技术**避免了每次清空大数组的开销，是一个值得掌握的优化技巧。


核心: 

 - 贪心: 最大不相交区间数量
 - 数学: 异或区间和,异或前缀和
